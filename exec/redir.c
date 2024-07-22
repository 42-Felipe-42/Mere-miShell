/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:33:30 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/22 09:48:19 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_fd(t_fd *fd)
{
	fd->redir[0] = -2;
	fd->redir[1] = -2;
	fd->pipes[1] = -2;
	fd->pipes[0] = -2;
	fd->output = -2;
}

int	handle_input_redir(t_lexer *redirs, t_cmds *cmd, int fd, t_shell *shell)
{
	if (fd != -1)
		close(fd);
	printf("test33\n");
	if (redirs->token == IN_REDIR)
	{
		fd = open(redirs->word, O_RDONLY);
		if (fd == -1)
		{
			perror(redirs->word);
		}
		printf("test2\n");
	}
	else if (redirs->token == HERE_DOC)
	{
		fd = here_doc(cmd, shell);
		printf("test1\n");
		// Assurez-vous que here_doc() gère les erreurs
	}
	return (fd);
}

int	handle_output_redir(t_lexer *redirs, int fd)
{
	if (fd != -1)
		close(fd);
	if (redirs->token == OUT_REDIR)
	{
		fd = open(redirs->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(redirs->word);
		}
	}
	else if (redirs->token == APPEND)
	{
		fd = open(redirs->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(redirs->word);
		}
	}
	return (fd);
}

void	process_redirections(t_cmds *cmds, int *fd_in, int *fd_out,
		t_shell *shell)
{
	t_lexer	*redirs;

	redirs = cmds->lex_redir;
	while (redirs)
	{
		if (redirs->token == IN_REDIR || redirs->token == HERE_DOC)
		{
			*fd_in = handle_input_redir(redirs, cmds, *fd_in, shell);
		}
		else if (redirs->token == OUT_REDIR || redirs->token == APPEND)
		{
			*fd_out = handle_output_redir(redirs, *fd_out);
		}
		if ((*fd_in == -1) || (*fd_out == -1))
			break ;
		redirs = redirs->next;
	}
}

void	set_fds(t_fd *fd)
{
	if (fd->pipes[1] != -2)
		fd->output = fd->pipes[1];
	if (fd->redir[0] != -2)
	{
		if (fd->input != -2)
			close(fd->input);
		fd->input = fd->redir[0];
	}
	if (fd->redir[1] != -2)
	{
		if (fd->pipes[1] != -2)
			close(fd->pipes[1]);
		fd->output = fd->redir[1];
	}
}
