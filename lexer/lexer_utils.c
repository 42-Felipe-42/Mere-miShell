/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:51:21 by plangloi          #+#    #+#             */
/*   Updated: 2024/08/22 16:31:10 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// verifie si input[*i] est un symbol redir
int	which_redir(char *input, int *i)
{
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
		return (TRUE);
	return (FALSE);
}

// verifie si input[i] est un guillmet
int	which_quote(char input)
{
	if (!input)
		return (0);
	if (input == '\'')
		return (1);
	else if (input == '\"')
		return (2);
	else
		return (0);
}

// si token trouve dans input[i], return sa valeur associee, sinon return false
int	is_token(char *input, int *i)
{
	if (input[*i] == '|')
		return (PIPE);
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
			return ((*i)++, HERE_DOC);
		else
			return (IN_REDIR);
	}
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
			return ((*i)++, APPEND);
		else
			return (OUT_REDIR);
	}
	return (FALSE);
}
void	is_quoted(char *input, int *i, int *opened)
{
	*opened = which_quote(input[*i]);
	(*i)++;
	while (*opened && input[*i])
	{
		if (*opened == which_quote(input[*i]))
			*opened = 0;
		(*i)++;
	}
}
// parcour le input du premier au dernier quote identique

// parcour input en i tant que diff token, quotes et espace
void	is_word(char *input, int *i)
{
	while (input[*i] && input[*i] != ' ' && which_redir(input, i) == FALSE
		&& !which_quote(input[*i]))
	{
		(*i)++;
	}
}
