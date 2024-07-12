/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:33:30 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/12 19:26:50 by felipe           ###   ########.fr       */
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

void	set_intput(t_cmds *cmds, t_fd *fd)
{
	if (fd->redir[0] != -2 && fd->redir[0] != -1)
		close(fd->redir[0]);
	if (cmds->lex_redir->token == IN_REDIR)
	{
		fd->redir[0] = open(cmds->lex_redir->word, O_RDONLY, 0644);
		if (fd->redir[0] == -1)
			perror(cmds->lex_redir->word), close_all_fds(fd);
	}
	else if (cmds->lex_redir->token == HERE_DOC)
	{
		fd->redir[0] = here_doc(cmds);
	}
}

void	set_output(t_cmds *cmds, t_fd *fd)
{
	if (fd->redir[1] != -2)
		close(fd->redir[1]);
	if (cmds->lex_redir->token == APPEND)
	{
		fd->redir[1] = open(cmds->lex_redir->word,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd->redir[1] == -1)
			perror(cmds->lex_redir->word), close_all_fds(fd);
	}
	else if (cmds->lex_redir->token == OUT_REDIR)
	{
		fd->redir[1] = open(cmds->lex_redir->word, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		printf("fd redir[1] set %d\n", fd->redir[1]);
		if (fd->redir[1] == -1)
			perror(cmds->lex_redir->word), close_all_fds(fd);
	}
}

void	set_redir(t_cmds *cmds, t_fd *fd)
{
	t_cmds	*curr;

	curr = cmds;
	while (curr)
	{
		is_builtin(cmds);
		if (cmds->lex_redir && cmds->lex_redir->token != 0)
		{
			if (cmds->lex_redir->token == IN_REDIR
				|| cmds->lex_redir->token == HERE_DOC)
				set_intput(cmds, fd);
			else if (cmds->lex_redir->token == OUT_REDIR
				|| cmds->lex_redir->token == APPEND)
				set_output(cmds, fd);
			printf("fd redir[1] set %d\n", fd->redir[1]);
		}
		curr = curr->next;
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