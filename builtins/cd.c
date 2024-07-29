/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:48:18 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/29 15:27:17 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int change_dir(t_shell *shell, t_cmds *cmds)
{
	if (chdir(cmds->tab[1]) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(cmds->tab[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		shell->exit_code = 1;
		return (1);
	}
	return (0);
}

static int go_home(t_shell *shell, char *old_pwd)
{
	char *home_dir;
	t_env *env_entry;

	env_entry = shell->env;
	home_dir = ft_strdup("");
	if (!home_dir)
		exit_and_free(shell, "Error : malloc failed");
	while (env_entry && env_entry->next)
	{
		if (!ft_strncmp(env_entry->key, "HOME=", 4))
		{
			free(home_dir);
			home_dir = ft_strdup(env_entry->value);
			if (!home_dir)
				exit_and_free(shell, "Error : malloc failed");
			break;
		}
		env_entry = env_entry->next;
	}
	if (!home_dir)
		return (ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO),
				shell->exit_code = 1, 0);
	if (chdir(home_dir) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(home_dir, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (free(home_dir), free(old_pwd), shell->exit_code = 1, 0);
	}
	return (free(home_dir), 0);
}
void print_env_list(t_env *env_list)
{
	t_env *current;

	current = env_list;
	while (current)
	{
		printf(" %s: %s\n", current->key, current->value);
		current = current->next;
	}
}
void update_env_vars(t_shell *shell, char *oldpwd, char *currpwd)
{
	t_env *env_entry;

	env_entry = shell->env;
	while (env_entry)
	{
		if (ft_strncmp(env_entry->key, "OLDPWD",
					   ft_strlen(env_entry->key)) == 0)
		{

			if (!oldpwd)
				return;
			free(env_entry->value);
			env_entry->value = ft_strdup(oldpwd);
			if (!env_entry->value)
			{
				free(oldpwd);
				exit_and_free(shell, "Error : malloc failed");
			}
		}
		if (ft_strncmp(env_entry->key, "PWD", ft_strlen(env_entry->key)) == 0)
		{
			free(env_entry->value);
			env_entry->value = ft_strdup(currpwd);
			if (!env_entry->value)
			{
				free(oldpwd);
				exit_and_free(shell, "Error : malloc failed");
			}
		}
		env_entry = env_entry->next;
	}
}
char *get_old(t_shell *shell)
{
	t_env *env;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->key, "OLDPWD", ft_strlen(env->key)) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}
void ft_cd(t_shell *shell, t_cmds *cmds)
{
	char *oldpwd;
	char *currpwd;

	if (cmds->tab[1] && cmds->tab[2])
	{
		shell->exit_code = 1;
		return (ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO));
	}
	oldpwd = get_old(shell);
	if (!cmds->tab[1])
	{
		if (!go_home(shell, oldpwd))
			return (free(oldpwd));
	}
	else if (change_dir(shell, cmds) == 1)
	{
		free(oldpwd);
		return;
	}
	currpwd = getcwd(NULL, 0);
	if (!currpwd)
	{
		perror("cd: error retrieving current directory: getcwd: \
			cannot access parent directories: No such file or directory");
		free(oldpwd);
		return;
	}
	update_env_vars(shell, oldpwd, currpwd);
	shell->exit_code = 0;
	free(oldpwd);
	free(currpwd);
}
