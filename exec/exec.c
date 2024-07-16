/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:39:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/16 18:06:41 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_child(t_shell *shell, t_cmds *cmds, t_fd *fds)
{
	if (fds->pipes[1] != -2)
		close(fds->pipes[0]);
	if (fds->input != -2)
		if (dup2(fds->input, STDIN_FILENO) == -1)
			(close_all_fds(fds), exit(1));
	if (fds->output != -2)
		if (dup2(fds->output, STDOUT_FILENO) == -1)
			(close_all_fds(fds), exit(1));
	close_all_fds(fds);
	get_cmds(shell->env, cmds);
}

void	execute_cmd(t_shell *shell, t_cmds *cmds, t_fd *fds)
{
	cmds->pid = fork();
	if (cmds->pid == -1)
		(close_all_fds(fds));
	if (cmds->pid == 0)
	{
		// if (cmds->builtin)
		// {
		// 	run_builtins(shell, cmds, fds, 1);
		// 	(close_all_fds(fds), exit(1));
		// }
		// else
		if (fds->redir[0] == -1 || fds->redir[1] == -1)
			exit(1);
		execute_child(shell, cmds, fds);
	}
	close_fds_parent(fds);
	fds->input = fds->pipes[0];
}

void	close_fds_parent(t_fd *fds)
{
	if (fds->input != -2 && fds->input >= 0)
		close(fds->input);
	if (fds->output != -2 && fds->output >= 0)
		close(fds->output);
}

void	run_exec(t_shell *shell)
{
	t_cmds *tmp_cmd;
	t_fd fds;

	fds.input = -2;
	tmp_cmd = shell->cmds;
	tmp_cmd->prev = NULL;
	while (tmp_cmd)
	{
		/* set_last_cmd(shell, tmp_cmd), */ init_fd(&fds);
		if (tmp_cmd->next)
			if (pipe(fds.pipes) == -1)
				exit(1);
		// exit_shell(shell, "pipe_creation", 1);
		process_redirections(tmp_cmd, &fds.redir[0], &fds.redir[1]);
		set_fds(&fds);
		// if (tmp_cmd->builtin && !tmp_cmd->next && !tmp_cmd->prev)
		// 	run_builtins(shell, tmp_cmd, &fds, 0);
		// if (tmp_cmd->tab[0])
		execute_cmd(shell, tmp_cmd, &fds);
		if (!tmp_cmd->next)
			close_fds_parent(&fds);
		if (tmp_cmd->next)
			tmp_cmd->next->prev = tmp_cmd;
		tmp_cmd = tmp_cmd->next;
	}
	(wait_child(shell), close_all_fds(&fds));
}