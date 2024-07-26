/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:33:41 by felipe            #+#    #+#             */
/*   Updated: 2024/07/26 17:04:02 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i] || (!ft_isalpha(str[i]) && str[i] != '_' ) )
		return (0);
	while (str[i])
	{
		if(which_quote(str[i]) && i == 0 )
			i++;
		if (!ft_isalnum(str[i]) && str[i] != '_' ) 
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
int	compare_env(const void *a, const void *b)
{
	t_env	*env_a;
	t_env	*env_b;

	env_a = *(t_env **)a;
	env_b = *(t_env **)b;
	return (ft_strcmp(env_a->key, env_b->key));
}
void	print_sorted_env(t_env *env)
{
	int		count;
	t_env	*temp;
	t_env	**env_array;

	count = 0;
	temp = env;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = malloc(count * sizeof(t_env *));
	temp = env;
	for (int i = 0; i < count; i++)
	{
		env_array[i] = temp;
		temp = temp->next;
	}
	qsort(env_array, count, sizeof(t_env *), compare_env);
	for (int i = 0; i < count; i++)
	{
		printf("declare -x %s=\"%s\"\n", env_array[i]->key,
			env_array[i]->value);
	}
	free(env_array);
}

void	ft_export(t_env **env, t_cmds *cmd)
{
	int		i;
	char	*arg;
	char	*equal_sign;

	i = 1;
	if (!cmd->tab[1])
	{
		print_sorted_env(*env);
		return ;
	}
	while (cmd->tab[i])
	{
		arg = cmd->tab[i];
		equal_sign = ft_strchr(arg, '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			if (is_valid_identifier(arg))
			{
				add_or_update_env(env, arg, equal_sign + 1);
			}
			else
			{
				fprintf(stderr,
					"minishell: export: `%s': not a valid identifier\n", arg);
			}
			*equal_sign = '=';
		}
		else
		{
			if (is_valid_identifier(arg))
			{
				add_or_update_env(env, arg, "");
			}
			else
			{
				fprintf(stderr,
					"minishell: export: `%s': not a valid identifier\n", arg);
			}
		}
		i++;
	}
}
