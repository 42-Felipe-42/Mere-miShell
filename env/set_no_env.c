/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_no_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:57:57 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/29 10:37:35 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	initialize_pwd(t_shell *shell)
{
	char	*current_directory;
	t_env	*new_entry;

	new_entry = ft_calloc(1, sizeof(t_env));
	current_directory = getcwd(NULL, 0);
	if (!new_entry || !current_directory)
		exit_and_free(shell, "Error : malloc failed initialize_pwd");
	new_entry->index = 1;
	new_entry->key = ft_strdup("PWD");
	if (!new_entry->key)
		exit_and_free(shell, "Error : malloc failed initialize_pwd");
	new_entry->value = ft_strdup(current_directory);
	if (!new_entry->value)
		exit_and_free(shell, "Error : malloc failed initialize_pwd");
	new_entry->prev = NULL;
	new_entry->next = NULL;
	shell->env = new_entry;
}

static void	initialize_shlvl(t_shell *shell)
{
	t_env	*new_entry;
	t_env	*current_entry;

	current_entry = shell->env;
	while (current_entry->next)
		current_entry = current_entry->next;
	new_entry = ft_calloc(1, sizeof(t_env));
	if (!new_entry)
		exit_and_free(shell, "Error : malloc failed initialize_shlvl");
	new_entry->index = 2;
	new_entry->key = ft_strdup("SHLVL");
	if (!new_entry->key)
		exit_and_free(shell, "Error : malloc failed initialize_shlvl");
	new_entry->value = ft_strdup("0");
	if (!new_entry->value)
		exit_and_free(shell, "Error : malloc failed initialize_shlvl");
	current_entry->next = new_entry;
	new_entry->next = NULL;
	new_entry->prev = current_entry;
}

static void	initialize_underscore(t_shell *shell)
{
	t_env	*new_entry;
	t_env	*current_entry;

	current_entry = shell->env;
	while (current_entry->next)
		current_entry = current_entry->next;
	new_entry = ft_calloc(1, sizeof(t_env));
	if (!new_entry)
		exit_and_free(shell, "Error : malloc failed initialize underscore");
	new_entry->index = 3;
	new_entry->key = ft_strdup("_");
	if (!new_entry->key)
		exit_and_free(shell, "Error : malloc failed initialize underscore");
	new_entry->value = ft_strdup("./minishell");
	if (!new_entry->value)
		exit_and_free(shell, "Error : malloc failed initialize underscore");
	current_entry->next = new_entry;
	new_entry->next = NULL;
	new_entry->prev = current_entry;
}

void	initialize_oldpwd(t_shell *shell)
{
	t_env	*current_entry;
	t_env	*new_entry;

	current_entry = shell->env;
	while (current_entry->next)
		current_entry = current_entry->next;
	new_entry = ft_calloc(1, sizeof(t_env));
	if (!new_entry)
		exit_and_free(shell, "Error : malloc failed initialize_oldpwd");
	new_entry->key = ft_strdup("OLDPWD");
	if (!new_entry->key)
		exit_and_free(shell, "Error : malloc failed initialize_oldpwd");
	new_entry->value = ft_strdup("OLDPWD");
	if (!new_entry->value)
		exit_and_free(shell, "Error : malloc failed initialize_oldpwd");
	new_entry->index = 4;
	current_entry->next = new_entry;
	new_entry->prev = current_entry;
	new_entry->next = NULL;
}

// Gestion de l'absence de variables d'environnement
void	handle_empty_env(t_shell *shell)
{
	initialize_pwd(shell);
	initialize_shlvl(shell);
	initialize_underscore(shell);
	initialize_oldpwd(shell);
}
