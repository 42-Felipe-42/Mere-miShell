/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:39:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/31 16:08:01 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void execute_child(t_shell *shell, t_cmds *cmds, t_fd *fds)
{
	find_path(shell->env , cmds, shell, fds);		
	if (fds->pipes[0] != -2)
		close(fds->pipes[0]);
	if (fds->input != -2)
		if (dup2(fds->input, STDIN_FILENO) == -1)
			(close_all_fds(fds), exit_and_free(shell, ""));
	if (fds->output != -2)
		if (dup2(fds->output, STDOUT_FILENO) == -1)
			(close_all_fds(fds), exit_and_free(shell, ""));
	close_all_fds(fds);
	get_cmds(shell->env, cmds, shell);
}

void execute_cmd(t_shell *shell, t_cmds *cmds, t_fd *fds)
{
	if (cmds->builtin == EXIT)
		ft_exit(shell, cmds, fds);
	if (cmds->builtin == CD)
		ft_cd(shell, cmds);
	else if (cmds->builtin == EXPORT)
		ft_export(&shell->env, cmds);
	else if (cmds->builtin == UNSET)
		ft_unset_builtin(shell, cmds);
	else
	{
		cmds->pid = fork();
		if (cmds->pid == -1)
			(close_all_fds(fds), exit_and_free(shell, "Error : Fork"));
		if (cmds->pid == 0)
		{
			if (cmds->builtin)
				(run_builtins(shell, cmds, fds),
				 close_all_fds(fds), exit_and_free(shell, ""));
			else
				execute_child(shell, cmds, fds);
		}
	}
	close_fds_parent(fds);
	fds->input = fds->pipes[0];
}
void update_last_cmd(t_shell *shell, t_cmds *cmds)
{
	t_env *tmp;
	char *last_cmd;

	tmp = shell->env;
	if (!cmds->tab)
		return;
	if (!cmds->tab[0])
		return;
	last_cmd = cmds->tab[0];
	while (tmp)
	{
		if (ft_strictcmp(tmp->key, "_") == 1)
		{
			free(tmp->value);
			tmp->value = ft_strdup(last_cmd);
			if (!tmp->value)
				(exit_and_free(shell, "Error : malloc failed"));
			return;
		}
		tmp = tmp->next;
	}
}
void run_exec(t_shell *shell)
{
	t_cmds *tmp_cmd;
	t_fd fds;

	fds.input = -2;
	tmp_cmd = shell->cmds;
	tmp_cmd->prev = NULL;
	while (tmp_cmd)
	{
		is_builtin(tmp_cmd);
		update_last_cmd(shell, tmp_cmd);
		init_fd(&fds);
		if (tmp_cmd->next)
			if (pipe(fds.pipes) == -1)
				exit_and_free(shell, "Error : pipe");
		process_redirections(tmp_cmd, &fds.redir[0], &fds.redir[1], shell);
		set_fds(&fds);
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
