/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/28 23:01:33 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_path(t_env *env, t_cmds *cmds)
{
	int		i;
	char	*path_found;
	char	*path;
	char	**path_env;

	while (env && ft_strnstr(env->key, "PATH", 5) == 0)
		env = env->next;
	if (!env)
		return (NULL);
	path_env = ft_split(env->value, ':');
	i = -1;
	while (path_env[++i])
	{
		path_found = ft_strjoin(path_env[i], "/");
		if (!path_found)
			return (free_split(path_env), exit(EXIT_FAILURE), NULL);
		path = ft_join_free(path_found, cmds->tab[0]);
		if (!path)
			return (free_split(path_env), free(path_found), exit(1), NULL);
		if (access(path, F_OK) == 0)
			return (free_split(path_env), path);
		free(path);
	}
	return (free_split(path_env), NULL);
}

void	ft_cmd_no_found(char *str)
{
	ft_putstr_fd("command not found : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**allocate_env_array(t_shell *shell, int count)
{
	char	**env_array;

	env_array = ft_calloc((count + 1), sizeof(char *));
	if (!env_array)
		exit_and_free(shell, "Error malloc env", 1);
	return (env_array);
}

char	*create_env_entry(char *key, char *value, t_shell *shell)
{
	char	*entry;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		exit_and_free(shell, "Error malloc env", 1);
	entry = ft_strjoin(tmp, value);
	if (!entry)
	{
		free(tmp);
		exit_and_free(shell, "Error malloc env", 1);
	}
	free(tmp);
	return (entry);
}
