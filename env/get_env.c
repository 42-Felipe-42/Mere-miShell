/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:38:17 by felipe            #+#    #+#             */
/*   Updated: 2024/07/31 17:23:09 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_env_key_value(t_shell *shell, t_env *new, char **envp, int i)
{
	char	*equal_sign;
	int		key_length;
	int		value_length;

	(void)shell;
	equal_sign = NULL;
	if (envp && envp[i])
		equal_sign = ft_strchr(envp[i], '=');
	else if (!equal_sign)
		exit_and_free(shell, "Error : malloc failed env");
	key_length = equal_sign - envp[i];
	value_length = ft_strlen(equal_sign + 1);
	new->key = ft_calloc(key_length + 1, sizeof(char));
	if (!new->key)
		exit_and_free(shell, "Error : malloc failed env");
	new->value = ft_calloc(value_length + 1, sizeof(char));
	if (!new->value)
	{
		free(new->key);
		exit_and_free(shell, "Error : malloc failed env_value");
	}
	ft_strncpy(new->key, envp[i], key_length);
	ft_strncpy(new->value, equal_sign + 1, value_length);
}

void	maj_env_node(t_shell *shell, t_env *new_env_node, char **envp,
		int index)
{
	t_env	*current;

	current = NULL;
	current = shell->env;
	new_env_node->index = index;
	set_env_key_value(shell, new_env_node, envp, index);
	new_env_node->next = NULL;
	new_env_node->prev = NULL;
	if (!current)
		shell->env = new_env_node;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_env_node;
		new_env_node->prev = current;
	}
}

char	*find_env(char *key, t_env *envp)
{
	int		len;
	t_env	*tmp_envp;

	tmp_envp = envp;
	len = ft_strlen(key);
	while (tmp_envp)
	{
		if (!ft_strncmp(key, tmp_envp->key, len) && tmp_envp->key[len] == '\0')
			return (tmp_envp->value);
		tmp_envp = tmp_envp->next;
	}
	return (NULL);
}

void	get_env(t_shell *shell, char **envp)
{
	int index;
	t_env *new_env_node;

	index = 0;
	if (!envp || !envp[0])
	{
		handle_empty_env(shell);
		return ;
	}
	while (envp[index])
	{
		new_env_node = ft_calloc(1, sizeof(t_env));
		if (!new_env_node)
			exit_and_free(shell, "Error : malloc failed get_env");
		maj_env_node(shell, new_env_node, envp, index);
		index++;
	}
}