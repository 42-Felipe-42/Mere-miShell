/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:14:19 by felipe            #+#    #+#             */
/*   Updated: 2024/08/23 10:11:46 by plangloi         ###   ########.fr       */
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

void	run_builtins(t_shell *shell, t_cmds *cmds, t_fd *fds)
{
	child_builtins(shell, fds);
	if (cmds->builtin == ECHO)
		ft_echo(shell, cmds, fds->output, fds);
	if (cmds->builtin == ENV)
		ft_env(shell, cmds, fds->output, fds);
	if (cmds->builtin == PWD)
		ft_pwd(cmds, shell, fds->output, fds);
}

void	child_builtins(t_shell *shell, t_fd *fds)
{
	if (fds->input != -2)
		close(fds->input);
	if (fds->output == -2)
		fds->output = dup(STDOUT_FILENO);
	if (fds->output == -1)
		(close_all_fds(fds), exit_and_free(shell, "Error : dup2"));
}

void	is_builtin(t_cmds *cmds)
{
	if (cmds && cmds->tab != NULL)
	{
		if (ft_strncmp(cmds->tab[0], "echo", 4) == 0
			&& ft_strlen(cmds->tab[0]) == 4)
			cmds->builtin = ECHO;
		else if (ft_strncmp(cmds->tab[0], "cd", 3) == 0
			&& ft_strlen(cmds->tab[0]) == 2)
			cmds->builtin = CD;
		else if (ft_strncmp(cmds->tab[0], "pwd", 3) == 0
			&& ft_strlen(cmds->tab[0]) == 3)
			cmds->builtin = PWD;
		else if (ft_strncmp(cmds->tab[0], "exit", 4) == 0
			&& ft_strlen(cmds->tab[0]) == 4)
			cmds->builtin = EXIT;
		else if (ft_strncmp(cmds->tab[0], "export", 6) == 0
			&& ft_strlen(cmds->tab[0]) == 6)
			cmds->builtin = EXPORT;
		else if (ft_strncmp(cmds->tab[0], "unset", 5) == 0
			&& ft_strlen(cmds->tab[0]) == 5)
			cmds->builtin = UNSET;
		else if (ft_strncmp(cmds->tab[0], "env", 3) == 0
			&& ft_strlen(cmds->tab[0]) == 3)
			cmds->builtin = ENV;
	}
}
