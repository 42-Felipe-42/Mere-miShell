/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:12:09 by lmerveil          #+#    #+#             */
/*   Updated: 2024/09/02 11:36:27 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quote_closed(char *word)
{
	int	len;

	len = ft_strlen(word);
	if ((len >= 2 && word[0] == '\'' && word[len - 1] == '\'') || (len >= 2
			&& word[0] == '\"' && word[len - 1] == '\"'))
		return (1);
	else
		return (0);
}

int	parser(t_lexer *lex, t_shell *shell)
{
	int		i;
	t_lexer	*lexer;
	char	*tmp;

	lexer = lex;
	if (syntaxe(lexer))
		return (1);
	while (lexer)
	{
		i = 0;
		while (lexer->word && lexer->word[i])
		{
			if (which_quote(lexer->word[i++]))
			{
				if (check_quote_closed(lexer->word) == 0)
					return (printf("Error : quote not closed\n"), 1);
				tmp = remove_quotes(lexer->word, shell);
				(free(lexer->word), lexer->word = tmp);
				break ;
			}
		}
		lexer = lexer->next;
	}
	return (free_lexer(&lexer), 0);
}
