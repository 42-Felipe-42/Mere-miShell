/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:39:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/23 18:09:09 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_child(t_shell *shell, t_cmds *cmds, t_fd *fds)
{
	if (fds->pipes[1] != -2)
		close(fds->pipes[0]);
	if (fds->input != -2)
		if (dup2(fds->input, STDIN_FILENO) == -1)
			(close_all_fds(fds), exit_and_free(shell, "dup2", 1));
	if (fds->output != -2)
		if (dup2(fds->output, STDOUT_FILENO) == -1)
			(close_all_fds(fds), exit_and_free(shell, "dup2", 1));
	close_all_fds(fds);
	get_cmds(shell->env, cmds, shell);
}

void	execute_cmd(t_shell *shell, t_cmds *cmds, t_fd *fds)
{
	// if (cmds->builtin == EXIT)
	// 	ft_exit(shell, cmds, fds);
	if (cmds->builtin == CD)
		ft_cd(shell, cmds);
	// else if (cmds->builtin == EXPORT)
	// 	ft_export(shell, cmds);
	// else if (cmds->builtin == UNSET)
	// 	ft_unset(shell, cmds);
	else
	{
		cmds->pid = fork();
		if (cmds->pid == -1)
			(close_all_fds(fds), exit_and_free(shell, "Error Fork", 1));
		if (cmds->pid == 0)
		{
			if (cmds->builtin)
				run_builtins(shell, cmds, fds);
			ft_putstr_fd("test built\n", 2);
			(close_all_fds(fds), exit (1));
		}
		else
		{
			execute_child(shell, cmds, fds);
			ft_putstr_fd("test child\n", 2);
		}
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
	t_cmds	*tmp_cmd;
	t_fd	fds;

	fds.input = -2;
	tmp_cmd = shell->cmds;
	tmp_cmd->prev = NULL;
	while (tmp_cmd)
	{
		is_builtin(tmp_cmd);
		printf("built %d\n", tmp_cmd->builtin);
		/* set_last_cmd(shell, tmp_cmd), */ init_fd(&fds);
		if (tmp_cmd->next)
			if (pipe(fds.pipes) == -1)
				exit_and_free(shell, "pipe", 1);
		process_redirections(tmp_cmd, &fds.redir[0], &fds.redir[1], shell);
		set_fds(&fds);
		// if (tmp_cmd->builtin && !tmp_cmd->next && !tmp_cmd->prev)
		// 	child_builtins(shell, tmp_cmd, &fds);
		if (tmp_cmd->tab && tmp_cmd->tab[0])
			execute_cmd(shell, tmp_cmd, &fds);
		if (!tmp_cmd->next)
			close_fds_parent(&fds);
		if (tmp_cmd->next)
			tmp_cmd->next->prev = tmp_cmd;
		tmp_cmd = tmp_cmd->next;
	}
	(wait_child(shell), close_all_fds(&fds));
}

// printf("fds.redir[0] %d\n", fds.redir[0]);
// printf("fds.redir[1] %d\n", fds.redir[1]);
// printf("fds.pipe[0] %d\n", fds.pipes[0]);
// printf("fds.pipe[1] %d\n", fds.pipes[1]);
// printf("fds.input %d\n", fds.input);
// printf("fds.output %d\n", fds.output);