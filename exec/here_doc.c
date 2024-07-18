/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:17:49 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/18 13:53:57 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	loop_here_doc(t_cmds *cmds, int fd)
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(cmds->lex_redir->next->word, "\n");
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, limiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(limiter);
}

int	here_doc(t_cmds *cmds, t_shell *shell)
{
	char	*file_name;
	t_fd	fd;
	int		tmp;

	file_name = ft_strdup("42");
	while (access(file_name, F_OK) == 0)
		file_name = ft_join_free(file_name, "42");
	tmp = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (tmp == -1)
		exit_and_free(shell, "Fail to open file", 1);
	fd.input = open(file_name, O_RDONLY);
	if (fd.input == -1)
		exit_and_free(shell, "Fail to open file", 1);
	unlink(file_name);
	loop_here_doc(cmds, tmp);
	free(file_name);
	close(tmp);
	return (fd.input);
}
