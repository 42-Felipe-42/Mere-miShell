/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:33:41 by felipe            #+#    #+#             */
/*   Updated: 2024/08/23 11:07:22 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i] || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void add_or_update_env(t_env **env, const char *key, const char *value)
{
    t_env *temp = *env;
    t_env *new_node;

    while (temp)
    {
        if (ft_strncmp(temp->key, key, ft_strlen(temp->key)) == 0)
        {
            free(temp->value);
            temp->value = ft_strdup(value);
            return;
        }
        temp = temp->next;
    }
    new_node = ft_calloc(1, sizeof(t_env));
    if (!new_node)
        exit_and_free(NULL, "Error: malloc failed");
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);k
    new_node->next = *env;
    if (*env)
        (*env)->prev = new_node;
    *env = new_node;
}

void	insertion_sort(t_env **arr, int n)
{
	t_env	*key;
	int		j;
	int		i;

	i = 1;
	while (i < n)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp(arr[j]->key, key->key) > 0)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
		i++;
	}
}

void	print_sorted_env(t_env *env, t_shell *shell, int count)
{
	t_env	*tmp;
	t_env	**env_array;
	int		i;

	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	env_array = malloc(count * sizeof(t_env *));
	if (!env_array)
		exit_and_free(shell, "Error : Malloc");
	tmp = env;
	i = -1;
	while (++i < count)
	{
		env_array[i] = tmp;
		tmp = tmp->next;
	}
	insertion_sort(env_array, count);
	i = -1;
	while (++i < count)
		printf("export %s=\"%s\"\n", env_array[i]->key, env_array[i]->value);
	free(env_array);
}

// Fonction principale pour exporter les variables d'environnement
void	ft_export(t_env **env, t_cmds *cmds, t_shell *shell)
{
	int		i;
	bool	skip;
	int		count;

	count = 0;
	i = 1;
	if (!cmds->tab[1])
	{
		print_sorted_env(*env, shell, count);
		return ;
	}
	while (cmds->tab[i])
	{
		skip = process_arg(env, cmds->tab[i], cmds->tab[i + 1]);
		if (skip)
			i++;
		i++;
	}
}
