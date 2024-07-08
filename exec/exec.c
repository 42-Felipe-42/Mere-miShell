/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:39:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/08 18:00:11 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec(t_cmds *cmds, t_env *env, t_shell *shell)
{
	t_fd	fd;
	int		i;
	int		fd_temp;

	i = 3;
	fd_temp = 0;
	if (cmds->lex_redir->token == HERE_DOC)
		fd.pipes[0] = here_doc(cmds);
	else
		first_child(cmds, &fd, env);
	while (cmds)
	{
		child_looping(fd_temp, &fd, cmds, env);
		cmds = cmds->next;
	}
	last_child(cmds, &fd, env);
	close_fd(&fd, fd_temp, 0);
	wait_children();
	return (EXIT_SUCCESS);
}
