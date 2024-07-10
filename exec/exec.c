/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:39:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/10 15:40:56 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_fd	init_fd(t_fd fd)
{
	fd.redir[0] = -2;
	fd.pipes[1] = -2;
	fd.pipes[0] = -2;
	fd.redir[1] = -2;
	fd.input = -2;
	fd.output = -2;
	return (fd);
}
void	exec(t_cmds **cmds, t_env *env /* , t_shell *shell */)
{
	t_fd	fd;
	int		fd_temp;
	t_cmds	*head;
	t_cmds **curr;
	head = *cmds;
	curr = cmds;
	fd_temp = 0;
	fd = init_fd(fd);
	while ((*curr)->next)
	{
		if ((*curr)->lex_redir->token != 0
			&& (*curr)->lex_redir->token == HERE_DOC)
			fd.pipes[0] = here_doc((*curr));
		else
		{
			first_child(head, &fd, env);
			(*curr) = (*curr)->next;
		}
		while (*curr && (*curr)->next && (*curr)->next->next)
		{
			child_looping(fd_temp, &fd, (*curr), env);
			*curr = (*curr)->next;
		}
		if (*curr && (*curr)->next == NULL)
			last_child((*curr), &fd, env);
		close_fd(&fd, fd_temp, 0);
		if (*curr && (*curr)->next != NULL)
			*curr = (*curr)->next;
	}
	wait_children();
	// return ;
}
// ls -l > test | cat < test1