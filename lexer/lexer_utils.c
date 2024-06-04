/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:51:21 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/04 15:41:13 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int find_tokken(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '|')
			return (PIPE);
		if(input[i] =='<')
		{
			if (input[i+1] == '<')
				return (i++, M_LOWER);
			else
				return(LOWER);
		}
		if (input[i] == '>')
		{
			if (input[i+1] == '>')
				return (i++, M_BIGGER);
			else
				return(BIGGER);
		}
		i++;
	}
return(false);
}

int quote_de_porc(char input)
{
	if(input== '\'')
		return(1);
	else if (input == '\"')
		return(2);
	else 
		return(0);
}
