/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:12:09 by lmerveil          #+#    #+#             */
/*   Updated: 2024/08/01 14:44:05 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// copie des donnee de lex vers cmds->lex
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

t_lexer	*lex_to_cmds(t_lexer *lex, t_cmds **cmds, t_shell *shell)
{
	t_lexer	*tmp;
	int		count;
	int		i;

	i = 0;
	count = count_arg(lex);
	tmp = lex;
	(*cmds)->tab = ft_calloc(count + 1, sizeof(char *));
	if (!(*cmds)->tab)
		exit_and_free(shell, "Error malloc redir");
	while (tmp && tmp->word)
	{
		if (tmp->word)
		{
			(*cmds)->tab[i] = ft_strdup(tmp->word);
			if (!(*cmds)->tab[i])
			{
				for (int j = 0; j < i; j++)
					free((*cmds)->tab[j]);
				free((*cmds)->tab);
				exit_and_free(shell, "Error malloc redir");
			}
			i++;
		}
		if (tmp->next && tmp->next->word)
			tmp = tmp->next;
		else
			break ;
	}
	(*cmds)->tab[i] = NULL;
	return (tmp);
}

void	tmp_is_token(t_cmds *current_cmd, t_shell *shell)
{
	current_cmd->next = init_cmds(shell);
	current_cmd->next->prev = current_cmd;
	current_cmd = current_cmd->next;
}

void handle_pipe(t_cmds **current_cmd, t_shell *shell)
{
	(*current_cmd)->next = init_cmds(shell);
	(*current_cmd)->next->prev = *current_cmd;
	*current_cmd = (*current_cmd)->next;
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
			tmp = tmp->next;
			cmds->skip_redir = 1;
		}
		else if (tmp->token == PIPE)
			handle_pipe(&current_cmd, shell);
		else if ((tmp->next && tmp->next->token != PIPE)
			|| (!tmp->next && !cmds->skip_redir))
			tmp = lex_to_cmds(tmp, &current_cmd, shell);
		tmp = tmp->next;
	}
	return (free_lexer(&lex), cmds);
}


void	parser(t_lexer *lex, t_shell *shell)
{
	int		i;
	t_lexer	*lexer;
	char	*tmp;

	lexer = lex;
	i = 0;
	syntaxe(lexer, shell);
	expander(lexer, shell);
	while (lexer)
	{
		i = 0;
		while (lexer->word && lexer->word[i])
		{
			if (check_quote_closed(lexer->word) == FALSE)
				exit_and_free(shell, "Error : quote not closed");
			if (which_quote(lexer->word[i++]))
			{
				tmp = remove_quote(lexer->word, &i, shell);
				(free(lexer->word), lexer->word = tmp);
				break ;
			}
		}
		lexer = lexer->next;
	}
	free_lexer(&lexer);
}
