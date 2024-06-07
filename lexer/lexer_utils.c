/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:51:21 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/07 15:14:09 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// si token trouve dans input, return sa valeur associee, sinon return false
int find_token(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '|')
			return (PIPE);
		if(input[i] =='<')
		{
			if (input[i+1] == '<')
				return (i++, HERE_DOC);
			else
				return(IN_REDIR);
		}
		if (input[i] == '>')
		{
			if (input[i+1] == '>')
				return (i++, APPEND);
			else
				return(OUT_REDIR);
		}
		i++;
	}
return(FALSE);
}

int is_token(char *input, int *i)
{

	if (input[*i] == '|')
		return (PIPE);
	if(input[*i] =='<')
	{
		if (input[*i+1] == '<')
			return ((*i)++, HERE_DOC);
		else
			return(IN_REDIR);
	}
	if (input[*i] == '>')
	{
		if (input[*i+1] == '>')
			return ((*i)++, APPEND);
		else
			return(OUT_REDIR);
	}
return(FALSE);
}

// verifie si input[i] est un guillmet
int quote_de_porc(char input)
{
	if(input == '\'')
		return(1);
	else if (input == '\"')
		return(2);
	else 
		return(0);
}

