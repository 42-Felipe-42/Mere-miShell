/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:49:39 by plangloi          #+#    #+#             */
/*   Updated: 2024/08/23 12:08:07 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tmp_is_token(t_cmds **current_cmd, t_shell *shell)
{
	(*current_cmd)->next = init_cmds(shell);
	(*current_cmd)->next->prev = *current_cmd;
	*current_cmd = (*current_cmd)->next;
}

int	check_quote_closed(char *word)
{
	int	d_quote;
	int	i;
	int	s_quote;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (word[i])
	{
		if (which_quote(word[i]) == D_QUOTE)
			d_quote++;
		if (which_quote(word[i]) == S_QUOTE)
			s_quote++;
		i++;
	}
	if (s_quote % 2 != 0 || d_quote % 2 != 0)
		return (FALSE);
	return (TRUE);
}

int	count_arg(t_lexer *lex)
{
	int	count;

	count = 1;
	while (lex && lex->next && lex->next->token != PIPE)
	{
		count++;
		lex = lex->next;
	}
	return (count);
}

void	syntaxe(t_lexer *lex, t_shell *shell)
{
	t_lexer	*tmp;

	tmp = lex;
	if (tmp && tmp->token == PIPE)
	{
		free_lexer(&lex);
		exit_and_free(shell, "Error : syntax error near unexpected token");
	}
	while (tmp)
	{
		if (tmp->token == PIPE && (!tmp->next || tmp->next->token == PIPE))
		{
			free_lexer(&lex);
			exit_and_free(shell, "Error : syntax error near unexpected token");
		}
		if ((tmp->token != 0 && tmp->token != PIPE) && ((tmp->next == NULL)
				|| (tmp->next->token != 0)))
		{
			free_lexer(&lex);
			exit_and_free(shell, "Error : syntax error near unexpected token");
		}
		tmp = tmp->next;
	}
}

char	*remove_quotes(char *str, t_shell *shell)
{
	int		i;
	int		j;
	int		length;
	char	*result;

	i = 0;
	j = 0;
	length = ft_strlen(str);
	result = (char *)malloc(length + 1);
	if (!result)
	{
		perror("Erreur d'allocation mémoire");
		exit_and_free(shell, "ERROR : malloc");
	}
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
