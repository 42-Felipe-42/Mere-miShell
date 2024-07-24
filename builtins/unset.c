/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:24:43 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/24 13:57:40 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*find_env_node(t_shell *shell, const char *key)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)

		{ // Utilisez strcmp pour une comparaison complète
			printf("Found key: %s, Value: %s\n", current->key, current->value);
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

static void	unset_single_env(t_shell *shell, t_env *target)
{
	if (!target)
		return ;
	if (target == shell->env)
	{
		shell->env = target->next;
		if (shell->env)
			shell->env->prev = NULL;
	}
	else
	{
		if (target->prev)
			target->prev->next = target->next;
		if (target->next)
			target->next->prev = target->prev;
	}
	free(target->key);
	free(target->value);
	free(target);
}

static void	unset_multiple_envs(t_shell *shell, char **keys)
{
	t_env	*target;
	int		i;

	i = 1;
	while (keys[i])
	{
		target = find_env_node(shell, keys[i]);
		printf("key [%d]%s\n", i, keys[i]);
		unset_single_env(shell, target);
		i++;
	}
}

void	ft_unset_builtin(t_shell *shell, t_cmds *cmds)
{
	if (!cmds->tab[1])
	{
		shell->exit_code = 1;
		return ;
	}
	unset_multiple_envs(shell, cmds->tab);
	shell->exit_code = 0;
}