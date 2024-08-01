/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:15:04 by louismdv          #+#    #+#             */
/*   Updated: 2024/08/01 09:40:04 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_custom_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

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

// Fonction pour traiter un argument
bool	process_arg(t_env **env, char *arg, char *next_arg)
{
	char	*equal_sign;
	char	*joined_arg;
	bool	skip_next;

	joined_arg = NULL;
	skip_next = false;
	trim_spaces(arg);
	if (arg && arg[strlen(arg) - 1] == '=' && next_arg)
	{
		joined_arg = ft_strjoin(arg, next_arg);
		if (!joined_arg)
			return (ft_putstr_fd("Error: malloc\n", STDERR_FILENO), false);
		arg = joined_arg;
		skip_next = true;
	}
	equal_sign = strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		handle_assignment(env, arg, equal_sign);
		*equal_sign = '=';
	}
	else
		handle_identifier(env, arg);
	if (joined_arg)
		free(joined_arg);
	return (skip_next);
}

// Fonction principale pour exporter les variables d'environnement
void	ft_export(t_env **env, t_cmds *cmds)
{
	int		i;
	bool	skip;

	i = 1;
	if (!cmds->tab[1])
	{
		print_sorted_env(*env);
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
