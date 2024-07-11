/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:39:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/11 14:14:27 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	exec(t_cmds **cmds, t_env *env /* , t_shell *shell */)
{
	t_fd	fd;
	int		fd_temp;
	t_cmds	*head;
	t_cmds	**curr;

	head = *cmds;
	curr = cmds;
	fd_temp = 0;
	while ((*curr))
	{
		init_fd(&fd);
		if ((*curr)->lex_redir->token != 0
			&& (*curr)->lex_redir->token == HERE_DOC)
			fd.redir[0] = here_doc((*curr));
		else
		{
			first_child(head, &fd, env);
			(*curr) = (*curr)->next;
		}
		printf("pipes[1] %d\n", fd.pipes[1]);
		printf("pipes[0] %d\n\n", fd.pipes[0]);
		while (*curr && (*curr)->next && (*curr)->next->next)
		{
			child_looping(fd_temp, &fd, (*curr), env);
			*curr = (*curr)->next;
		}
		if (*curr && (*curr)->next == NULL)
			last_child((*curr), &fd, env);
		// close_fd(&fd, fd_temp, 0);
		if (*curr && (*curr)->next != NULL)
			*curr = (*curr)->next;
	}
	wait_children();
	// return ;
}
// ls -l > test | cat < test1