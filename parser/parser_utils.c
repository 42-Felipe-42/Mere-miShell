/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:49:39 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/12 11:11:36 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quote_closed(t_lexer *lex)
{
	t_lexer	*checker;
	int		quote;
	int		i;

	quote = 0;
	checker = lex;
	while (checker)
	{
		i = 0;
		while (checker->word[i])
		{
			if (which_quote(checker->word[i]))
				quote++;
			i++;
		}
		checker = checker->next;
	}
	if (quote % 2 == 0)
		return (TRUE);
	else
		return (FALSE);
}
