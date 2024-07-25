/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:53:08 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/25 11:01:13 by plangloi         ###   ########.fr       */
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

void free_cmds(t_cmds **cmd)
{
    t_cmds *tmp;
    t_lexer *cmdlex;

    if (!cmd || !*cmd)
        return;
    while (*cmd)
    {
        cmdlex = (*cmd)->lex_redir;
        free_lexer(&cmdlex);  // Libération de redir
        if ((*cmd)->tab)
            free_split((*cmd)->tab);  // Libération de tab
        if ((*cmd)->path)
            free((*cmd)->path);  // Libération de path
        tmp = (*cmd)->next;
        free(*cmd);
        *cmd = tmp;
    }
    *cmd = NULL;  // Mettre le pointeur à NULL après libération
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