/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:53:08 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/25 10:59:05 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_lexer(t_lexer **lex)
{
	t_lexer	*to_free;

	if (!(*lex))
		return ;
	while (*lex)
	{
		to_free = *lex;
		*lex = (*lex)->next;
		to_free->next = NULL;
		free(to_free->word);
		free(to_free);
	}
}

void	free_cmds(t_cmds **cmds)
{
	t_cmds	*tmp;
	t_cmds	*next;
	int		i;

	if (!cmds || !*cmds)
		return ;
	tmp = *cmds;
	while (tmp)
	{
		i = 0;
		next = tmp->next;
		if (tmp->tab)
		{
			while (tmp->tab[i])
			{
				free(tmp->tab[i]);
				i++;
			}
			free(tmp->tab);
		}
		if (tmp->path)
			free(tmp->path);
		if (tmp->lex_redir)
			free_lexer(&(tmp->lex_redir));
		tmp = next;
	}
	*cmds = NULL; // Mettre le pointeur à NULL après libération
}

void	free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*next;

	if (!env)
		return ;
	tmp = env;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->value)
			free(tmp->value);
		if (tmp->key)
			free(tmp->key);
		free(tmp);
		tmp = next;
	}
	env = NULL;
}

void	free_shell(t_shell *shell)
{
	if (shell->cmds)
		free_cmds(&shell->cmds);
	if (shell->env)
		free_env(shell->env);
	if (shell->lex)
		free_lexer(&shell->lex);
	if (shell->av)
		free(shell->av);
	if (shell)
		free(shell);
}

void	ft_freeshell(t_shell *shell)
{
	t_env *env;
	t_cmds *cmd;

	env = shell->env;
	cmd = shell->cmds;
	free_env(env);
	free_cmds(&cmd);
	free(shell->av);
	if (shell)
		free(shell);
}