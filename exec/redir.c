/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:33:30 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/11 17:25:05 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_fd(t_fd *fd)
{
	fd->redir[1] = -2;
	fd->pipes[1] = -2;
	fd->pipes[0] = -2;
	fd->output = -2;
	fd->input = -2;
}

void	set_intput(t_cmds *cmds, t_fd *fd)
{
	if (fd != -2)
		close(fd);
	if (cmds->lex_redir->token == IN_REDIR)
	{
		fd->output = open(cmds->lex_redir->word, O_RDONLY, 0644);
		if (fd->output == -1)
			return (perror(cmds->lex_redir->word), close_fd(fd, fd->output, 2),
				exit(EXIT_FAILURE), 1);
	}
	else if (cmds->lex_redir->token == HERE_DOC)
	{
		fd->output = here_doc(cmds);
	}
}

void	set_output(t_cmds *cmds, t_fd *fd)
{
	if (fd != -2)
		close(fd);
	if (cmds->lex_redir->token == APPEND)
	{
		fd->input = open(cmds->lex_redir->word, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (fd->input == -1)
			return (perror(cmds->lex_redir->word), close_fd(fd, fd->input, 2),
				exit(EXIT_FAILURE), 1);
	}
	else if (cmds->lex_redir->token == OUT_REDIR)
	{
		fd->input = open(cmds->lex_redir->word, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (fd->input == -1)
			return (perror(cmds->lex_redir->word), close_fd(fd, fd->input, 2),
				exit(EXIT_FAILURE), 1);
	}
}

void	set_redir(t_cmds *cmds, t_fd *fd)
{
	t_cmds *curr;

	curr = cmds;
	while (curr)
	{
		if (cmds->lex_redir->token == IN_REDIR
			|| cmds->lex_redir->token == HERE_DOC)
			set_intput(cmds, fd);
		else if (cmds->lex_redir->token == OUT_REDIR
			|| cmds->lex_redir->token == APPEND)
			set_output(cmds, fd);
		curr = curr->next;
	}
}

void set_fds(t_fd *fd)
{
	if (fd->pipes[1] != -2)
		fd->output = fd->pipes[1];
	if (fd->redir[0] != -2)
	{
		if (fd->input != -2)
			close (fd->input);
		fd->input = fd->redir[0];
	}
	if(fd->redir[1] != -2)
	{
		if(fd->pipes[1] != -2)
			close(fd->pipes[1]);
		fd->output = fd->redir[1];
	}
}