/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:48:18 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/29 01:18:12 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	change_dir(t_shell *shell, t_cmds *cmds, int i, char *home_dir)
{
	(void)shell;
	if (chdir(cmds->tab[1]) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		if (i == 2)
			ft_putstr_fd(cmds->tab[1], STDERR_FILENO);
		else
			ft_putstr_fd(home_dir, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		shell->exit_code = 15;
		return (1);
	}
	return (0);
}

static int	go_home(t_shell *shell, char *old_pwd)
{
	char	*home_dir;
	t_env	*env_entry;

	env_entry = shell->env;
	home_dir = ft_strdup("");
	if (!home_dir)
		exit_and_free(shell, "malloc failed", 1);
	while (env_entry && env_entry->next)
	{
		if (!ft_strncmp(env_entry->key, "HOME=", 4))
		{
			free(home_dir);
			home_dir = ft_strdup(env_entry->value);
			if (!home_dir)
				exit_and_free(shell, "malloc failed", 1);
			break ;
		}
		env_entry = env_entry->next;
	}
	if (!home_dir)
		return (ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO),
			shell->exit_code = 1, 0);
	if (chdir(home_dir) == -1)
	{
		change_dir(shell, shell->cmds, 1, home_dir);
		printf("code: %d\n", shell->exit_code);
		return (free(home_dir), free(old_pwd), 0);
	}
	return (free(home_dir), 0);
}

void	update_env_vars(t_shell *shell, char *oldpwd, char *currpwd)
{
	t_env	*env_entry;

	env_entry = shell->env;
	while (env_entry)
	{
		if (ft_strcmp(env_entry->key, "OLDPWD"))
		{
			if (!oldpwd)
				return ;
			free(env_entry->value);
			env_entry->value = ft_strdup(oldpwd);
		}
		else if (ft_strcmp(env_entry->key, "PWD"))
		{
			free(env_entry->value);
			env_entry->value = ft_strdup(currpwd);
		}
		if (!env_entry->value)
		{
			free(oldpwd);
			exit_and_free(shell, "malloc failed", 1);
		}
		env_entry = env_entry->next;
	}
}

void	ft_cd(t_shell *shell, t_cmds *cmds)
{
	char	*oldpwd;
	char	*currpwd;

	if (cmds->tab[1] && cmds->tab[2])
	{
		shell->exit_code = 1;
		return (ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO));
	}
	oldpwd = getcwd(NULL, 0);
	if (!cmds->tab[1])
	{
		if (!go_home(shell, oldpwd))
			return (free(oldpwd));
	}
	else if (!change_dir(shell, cmds, 2, NULL))
		{printf("code: %d\n", shell->exit_code);

		return (free(oldpwd));}
	currpwd = getcwd(NULL, 0);
	update_env_vars(shell, oldpwd, currpwd);
	shell->exit_code = 0;
	free(oldpwd);
	free(currpwd);
}
