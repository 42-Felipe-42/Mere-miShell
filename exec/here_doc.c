/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:43:46 by plangloi          #+#    #+#             */
/*   Updated: 2024/08/01 09:43:51 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrlc(t_shell *shell, t_fd *fd)
{
	if (g_signal == SIGINT)
	{
		shell->exit_code = 130;
		g_signal = 0;
		close(fd->input);
		dup2(fd->input, STDIN_FILENO);
	}
}

void	loop_here_doc(t_lexer *redirs, int fd)
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(redirs->word, "\n");
	while (1)
	{
		line = readline(">");
		if (line == NULL || (!ft_strncmp(line, limiter, ft_strlen(line))
				&& ft_strlen(line) != 0))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	free(limiter);
}

int	here_doc(t_shell *shell, t_lexer *redirs)
{
	char	*file_name;
	t_fd	fd;
	int		tmp;

	file_name = ft_strdup("42");
	while (access(file_name, F_OK) == 0)
		file_name = ft_join_free(file_name, "42");
	tmp = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (tmp == -1)
		exit_and_free(shell, "Error : Fail to open file");
	fd.input = open(file_name, O_RDONLY);
	if (fd.input == -1)
		exit_and_free(shell, "Error : Fail to open file");
	unlink(file_name);
	loop_here_doc(redirs, tmp);
	free(file_name);
	close(tmp);
	ctrlc(shell, &fd);
	return (fd.input);
}
