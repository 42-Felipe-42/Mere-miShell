/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:12:09 by lmerveil          #+#    #+#             */
/*   Updated: 2024/07/16 18:15:57 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// copie des donnee de lex vers cmds->lex
void	redir_to_cmds(t_lexer *lex, t_cmds **cmds)
{
	t_lexer	*tmp;
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return ;
	new_node->token = lex->token;
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

t_lexer	*lex_to_cmds(t_lexer *lex, t_cmds **cmds)
{
	t_lexer	*tmp;
	int		count;
	int		i;

	i = 0;
	count = count_pipes(lex) + 1;
	tmp = lex;
	if (cmds == NULL)
		cmds = malloc(sizeof(t_cmds));
	(*cmds)->tab = malloc((count + 1) * (sizeof(char *)));
	while (tmp && tmp->word)
	{
		if (tmp->word)
			(*cmds)->tab[i] = ft_strdup(tmp->word);
		if (!(*cmds)->tab)
			return (NULL);
		i++;
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	(*cmds)->tab[i] = NULL;
	return (tmp);
}

t_cmds	*create_cmds(t_lexer *lex)
{
	t_lexer	*tmp;
	t_cmds	*cmds;
	t_cmds	*current_cmd;
	int		skip_redir;

	cmds = init_cmds();
	current_cmd = cmds;
	tmp = lex;
	skip_redir = 0;
	while (tmp)
	{
		if (tmp->token == IN_REDIR || tmp->token == OUT_REDIR
			|| tmp->token == APPEND)
		{
			skip_redir = 0;
			redir_to_cmds(tmp, &current_cmd);
			skip_redir = 1;
		}
		else if (tmp->token == PIPE)
		{
			current_cmd->next = init_cmds();
			current_cmd->next->prev = current_cmd;
			current_cmd = current_cmd->next;
		}
		else if (tmp->next && tmp->next->token != PIPE)
			tmp = lex_to_cmds(tmp, &current_cmd);
		tmp = tmp->next;
	}
	return (cmds);
}

void	parser(t_lexer *lex)
{
	int		i;
	t_lexer	*lexer;

	lexer = lex;
	i = 0;
	syntaxe(lexer);
	while (lexer)
	{
		i = 0;
		while (lexer->word && lexer->word[i])
		{
			if (check_quote_closed(lex->word) == FALSE)
			{
				printf("test\n");
				exit(1);
			}
			if (which_quote(lexer->word[i]))
			{
				lexer->word = remove_quote(lexer->word, &i);
				break ;
			}
			i++;
		}
		lexer = lexer->next;
	}
}
