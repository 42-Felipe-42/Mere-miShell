/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/29 10:37:51 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		exit_and_free(shell, "Error : malloc failed env");
	return (env_array);
}

char	*create_env_entry(char *key, char *value, t_shell *shell)
{
	char	*entry;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		exit_and_free(shell, "Error : malloc failed env");
	entry = ft_strjoin(tmp, value);
	free(tmp);
	if (!entry)
		exit_and_free(shell, "Error : malloc failed env");
	return (entry);
}

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
		exit_and_free(shell, "Error : malloc failed env");
	}
	return (env_array);
}
