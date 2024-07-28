/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/28 23:16:34 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fill_env_array(t_env *env, char **env_array, t_shell *shell)
{
	t_env	*tmp;
	int		i;
	int		j;

	tmp = env;
	i = 0;
	while (tmp)
	{
		j = 0;
		env_array[i] = create_env_entry(tmp->key, tmp->value, shell);
		if (!env_array[i])
		{
			while (j < i)
			{
				free(env_array[j]);
				j++;
			}
			return (-1);
		}
		tmp = tmp->next;
		i++;
	}
	env_array[i] = NULL;
	return (0);
}

char	**convert_env_to_array(t_env *env, t_shell *shell)
{
	int		count;
	char	**env_array;

	count = count_env_vars(env);
	env_array = allocate_env_array(shell, count);
	if (!env_array)
		return (NULL);
	if (fill_env_array(env, env_array, shell) == -1)
	{
		free(env_array);
		exit_and_free(shell, "Error convert env", 1);
	}
	return (env_array);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}
