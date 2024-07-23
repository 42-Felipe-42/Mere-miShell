/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:14:19 by felipe            #+#    #+#             */
/*   Updated: 2024/07/23 13:16:01 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Your shell must implement the following builtins:
// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

void	builtins_fds(t_shell *shell, t_fd *fds)
{
	if (fds->input != -2)
		close(fds->input);
	if (fds->output == -2)
		fds->output = dup(STDOUT_FILENO);
	if (fds->output == -1)
		(close_all_fds(fds), exit_and_free(shell, "dup2", 1));
}

void	run_builtins(t_shell *shell, t_cmds *cmds, t_fd *fds, int flag)
{
	(void)flag;
	builtins_fds(shell, fds);
	if (cmds->builtin == ECHO)
		ft_echo(shell, cmds);
	// if (cmds->builtin == CD)
	// 	cd_builtin(shell, cmds);
	// if (cmds->builtin == PWD)
	// 	pwd_builtin(shell, cmds, fds->output);
	// if (cmds->builtin == ENV)
	// 	env_builtin(shell, fds->output);
	// if (cmds->builtin == EXIT)
	// 	exit_builtin(shell, cmds, fds, flag);
	// if (cmds->builtin == UNSET)
	// 	unset_builtin(shell, cmds);
	// if (cmds->builtin == EXPORT)
	// 	export_builtin(shell, cmds, fds);
	printf(RED"\nbuiltins\n"RESET);
}

void	is_builtin(t_cmds *cmds)
{
	if (cmds && cmds->tab[0] != NULL)
	{
		if (ft_strncmp(cmds->tab[0], "echo", 4) == 0 && ft_strlen(cmds->tab[0]) == 4)
			cmds->builtin = ECHO;
		else if (ft_strcmp(cmds->tab[0], "cd") == 0 && ft_strlen(cmds->tab[0]) == 2)
			cmds->builtin = CD;
		else if (ft_strcmp(cmds->tab[0], "pwd") == 0 && ft_strlen(cmds->tab[0]) == 3)
			cmds->builtin = PWD;
		else if (ft_strcmp(cmds->tab[0], "export") == 0
			&& ft_strlen(cmds->tab[0]) == 6)
			cmds->builtin = EXPORT;
		else if (ft_strcmp(cmds->tab[0], "unset") == 0
			&& ft_strlen(cmds->tab[0]) == 5)
			cmds->builtin = UNSET;
		else if (ft_strcmp(cmds->tab[0], "env") == 0 && ft_strlen(cmds->tab[0]) == 3)
			cmds->builtin = ENV;
		else if (ft_strncmp(cmds->tab[0], "exit", 4) == 0
			&& ft_strlen(cmds->tab[0]) == 4)
			cmds->builtin = EXIT;
	}
}
void	child_builtin(t_shell *shell, t_cmds *cmd, t_fd *fd)
{
	(void)shell;
	(void)cmd;
	if (fd->pipes[0] != -42)
		close(fd->pipes[0]);
	if (fd->redir[0] != -42)
		if (dup2(fd->redir[0], STDIN_FILENO) == -1)
			(close_all_fds(fd)/* , exitmsg(shell, NULL) */);
	if (fd->redir[1] != -42)
		if (dup2(fd->redir[1], STDOUT_FILENO) == -1)
			(close_all_fds(fd)/* , exitmsg(shell, NULL) */);
	close_all_fds(fd);
/* 	if (cmd->builtin == ECHO)
		ft_echo(shell, cmd);
	if (cmd->builtin == ENV)
		ft_env(shell, cmd);
	if (cmd->builtin == PWD)
		ft_pwd(shell, cmd); */
}