/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:53:08 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/22 16:38:24 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_lexer(t_lexer **lex)
{
	t_lexer	*tmp;
	t_lexer	*next;

	if (!lex || !*lex)
		return ;
	tmp = *lex;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->word)
			free(tmp->word);
		free(tmp);
		tmp = next;
	}
	*lex = NULL;
}

void	free_cmds(t_cmds **cmds)
{
	t_cmds	*tmp;
	t_cmds	*next;

	if (!cmds || !*cmds)
		return ;
	tmp = *cmds;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->tab)
		{
			for (int i = 0; tmp->tab[i]; i++)
			{
				free(tmp->tab[i]);
				tmp->tab[i] = NULL;
			}
			free(tmp->tab);
			tmp->tab = NULL;
		}
		if (tmp->path)
		{
			free(tmp->path);
			tmp->path = NULL;
		}
		if (tmp->lex_redir)
		{
			free_lexer(&(tmp->lex_redir));
			tmp->lex_redir = NULL;
		}
		free(tmp);
		tmp = next;
	}
	*cmds = NULL;
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
	if (!shell)
		return ;
	if (shell->cmds)
	{
		free_cmds(&shell->cmds);
		shell->cmds = NULL;
	}
	if (shell->env)
	{
		free_env(shell->env);
		shell->env = NULL;
	}
	// if (shell->lex)
	// {
	//     free_lexer(&shell->lex);
	//     shell->lex = NULL;
	// }
	if (shell->av)
	{
		free(shell->av);
		shell->av = NULL;
	}
	free(shell);
}
