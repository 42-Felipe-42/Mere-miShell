/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:12:09 by lmerveil          #+#    #+#             */
/*   Updated: 2024/08/23 12:58:54 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parser(t_lexer *lex, t_shell *shell)
{
	int		i;
	t_lexer	*lexer;
	char	*tmp;

	lexer = lex;
	syntaxe(lexer, shell);
	while (lexer)
	{
		i = 0;
		while (lexer->word && lexer->word[i])
		{
			if (which_quote(lexer->word[i++]))
			{
				tmp = remove_quotes(lexer->word, shell);
				(free(lexer->word), lexer->word = tmp);
				break ;
			}
		}
		lexer = lexer->next;
	}
	free_lexer(&lexer);
}
