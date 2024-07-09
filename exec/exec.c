/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:39:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/09 15:55:26 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec(t_cmds *cmds, t_env *env /* , t_shell *shell */)
{
	t_fd	fd;
	int		fd_temp;
	int		i;

	i = 0;
	fd_temp = 0;
	while (cmds)
	{
		if (cmds->lex_redir->token == HERE_DOC)
			fd.pipes[0] = here_doc(cmds);
		else
		first_child(cmds, &fd, env);
		cmds = cmds->next;
		while (cmds && cmds->next && cmds->next->next)
		{
			child_looping(fd_temp, &fd, cmds, env);
			cmds = cmds->next;
			i++;
		}
		if (cmds && cmds->next == NULL)
			last_child(cmds, &fd, env);
		i++;
		printf("compteur %d\n", i);
		close_fd(&fd, fd_temp, 0);
		if (cmds && cmds->next != NULL)
			cmds = cmds->next;
	}
	wait_children();
	return ;
}
// ls -l > test | cat < test1