/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:15:04 by louismdv          #+#    #+#             */
/*   Updated: 2024/08/01 10:33:20 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Fonction pour supprimer les espaces autour des signes égaux
void	trim_spaces(char *str)
{
	char	*start;
	char	*end;

	start = str;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	*(end + 1) = '\0';
	if (start != str)
	{
		while (*start)
			*str++ = *start++;
		*str = '\0';
	}
}

// Fonction pour gerer les arguments avec un signe égal
void	handle_assignment(t_env **env, char *arg, char *equal_sign)
{
	trim_spaces(arg);
	trim_spaces(equal_sign + 1);
	if (is_valid_identifier(arg))
		add_or_update_env(env, arg, equal_sign + 1);
	else
		ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
}

// Fonction pour gérer les arguments sans signe égal
void	handle_identifier(t_env **env, char *arg)
{
	trim_spaces(arg);
	if (is_valid_identifier(arg))
		add_or_update_env(env, arg, "");
	else
		ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
}

void	free_joined(char *str)
{
	if (str)
		free(str);
}

// Fonction pour traiter un argument
bool	process_arg(t_env **env, char *arg, char *next_arg)
{
	char	*equal_sign;
	char	*joined_arg;
	bool	skip_next;

	skip_next = false;
	joined_arg = NULL;
	trim_spaces(arg);
	if (arg && arg[ft_strlen(arg) - 1] == '=' && next_arg)
	{
		joined_arg = ft_strjoin(arg, next_arg);
		if (!joined_arg)
			return (ft_putstr_fd("Error: malloc\n", STDERR_FILENO), false);
		arg = joined_arg;
		skip_next = true;
	}
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		handle_assignment(env, arg, equal_sign);
		*equal_sign = '=';
	}
	else
		handle_identifier(env, arg);
	return (free_joined(joined_arg), skip_next);
}
