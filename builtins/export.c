/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:33:41 by felipe            #+#    #+#             */
/*   Updated: 2024/07/31 11:38:47 by felipe           ###   ########.fr       */
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

void	add_or_update_env(t_env **env, const char *key, const char *value)
{
	t_env	*temp;
	t_env	*new_node;

	temp = *env;
	while (temp)
	{

		if (ft_strncmp(temp->key, key, ft_strlen(temp->key)) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
	new_node = ft_calloc(1, sizeof(t_env));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *env;
	*env = new_node;
}

int compare_env(const t_env *a, const t_env *b) {
    return ft_strcmp(a->key, b->key);
}

void insertion_sort(t_env **arr, int n, int (*cmp)(const t_env *, const t_env *)) {
    int i, j;
    t_env *key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && cmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void print_sorted_env(t_env *env) {
    int count = 0;
    int i;
    t_env *tmp = env;
    t_env **env_array;

    while (tmp) {
        count++;
        tmp = tmp->next;
    }

    env_array = malloc(count * sizeof(t_env *));
    if (!env_array) {
        // Handle memory allocation error
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    tmp = env;
    for (i = 0; i < count; i++) {
        env_array[i] = tmp;
        tmp = tmp->next;
    }

    // Replace qsort with insertion_sort
    insertion_sort(env_array, count, compare_env);

    for (i = 0; i < count; i++) {
        printf("declare -x %s=\"%s\"\n", env_array[i]->key, env_array[i]->value);
    }

    free(env_array);
}

void	ft_export(t_env **env, t_cmds *cmd)
{
	int		i;
	char	*arg;
	char	*equal_sign;
	char	*joined_arg;

	i = 1;
	if (!cmd->tab[1])
	{
		print_sorted_env(*env);
		return ;
	}
	while (cmd->tab[i])
	{
		arg = cmd->tab[i];
		joined_arg = NULL;
		if (arg[ft_strlen(arg) - 1] == '=' && cmd->tab[i + 1])
		{
			joined_arg = ft_strjoin(arg, cmd->tab[i + 1]);
			arg = joined_arg;
			i++;
		}
		equal_sign = ft_strchr(arg, '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			if (is_valid_identifier(arg))
				add_or_update_env(env, arg, equal_sign + 1);
			else
				fprintf(stderr,
					"minishell: export: `%s': not a valid identifier\n", arg);
			*equal_sign = '=';
		}
		else
		{
			if (is_valid_identifier(arg))
				add_or_update_env(env, arg, "");
			else
				fprintf(stderr,
					"minishell: export: `%s': not a valid identifier\n", arg);
		}
		if (joined_arg)
			free(joined_arg);
		i++;
	}
}
