/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:05:35 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/02 11:03:22 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmds	*init_cmds(t_shell *shell)
{
	t_cmds	*cmds;

	cmds = ft_calloc(1, sizeof(t_cmds));
	if (!cmds)
		exit_and_free(shell, "Error : malloc cmds");
	ft_bzero(cmds, sizeof(t_cmds));
	return (cmds);
}

void	redir_to_cmds(t_lexer *lex, t_cmds **cmds, t_shell *shell)
{
	t_lexer	*tmp;
	t_lexer	*new_node;

	new_node = ft_calloc(1, sizeof(t_lexer));
	if (!new_node)
		exit_and_free(shell, "Error :  malloc redir");
	new_node->token = lex->token;
	new_node->skip = lex->skip;
	if (lex->next->word)
		new_node->word = ft_strdup(lex->next->word);
	new_node->next = NULL;
	if ((*cmds)->lex_redir == NULL)
	{
		(*cmds)->lex_redir = new_node;
		return ;
	}
	tmp = (*cmds)->lex_redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	init_lex_to_cmds(t_lexer *lex, t_cmds **cmds, t_shell *shell)
{
	int	count;

	count = count_arg(lex);
	if (!(*cmds)->tab)
	{
		(*cmds)->tab = ft_calloc(count + 1, sizeof(char *));
		if (!(*cmds)->tab)
			exit_and_free(shell, "Error: malloc tab");
	}
	(*cmds)->spaces = ft_calloc(count, sizeof(int));
	if (!(*cmds)->spaces)
		exit_and_free(shell, "Error: malloc spaces");
}

t_lexer	*lex_to_cmds(t_lexer *lex, t_cmds **cmds, t_shell *shell)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = lex;
	init_lex_to_cmds(tmp, cmds, shell);
	while (tmp && tmp->word && tmp->token == 0)
	{
		if (tmp->word)
		{
			while ((*cmds)->tab && (*cmds)->tab[i])
				i++;
			(*cmds)->tab[i] = ft_strdup(tmp->word);
			(*cmds)->spaces[i] = tmp->space;
			if (!(*cmds)->tab[i++])
				(free_lexer(&tmp), exit_and_free(shell,
						"Error : malloc redir"));
		}
		tmp = tmp->next;
	}
	return ((*cmds)->tab[i] = NULL, tmp);
}

t_cmds	*create_cmds(t_lexer *lex, t_shell *shell)
{
	t_lexer	*tmp;
	t_cmds	*cmds;
	t_cmds	*current_cmd;

	cmds = init_cmds(shell);
	current_cmd = cmds;
	tmp = lex;
	while (tmp)
	{
		if (tmp->token == IN_REDIR || tmp->token == OUT_REDIR
			|| tmp->token == APPEND || tmp->token == HERE_DOC)
		{
			redir_to_cmds(tmp, &current_cmd, shell);
			tmp = tmp->next->next;
		}
		else if (tmp->token == PIPE)
		{
			tmp_is_token(&current_cmd, shell);
			tmp = tmp->next;
		}
		else if (((tmp->next && tmp->next->token == PIPE && tmp->next->next)
				|| (tmp->next && tmp->next->token != PIPE) || !tmp->next))
			tmp = lex_to_cmds(tmp, &current_cmd, shell);
	}
	return (free_lexer(&lex), shell->cmds = cmds, cmds);
}
