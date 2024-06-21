/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:49:39 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/21 16:00:02 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (s_quote % 2 == 0 || d_quote % 2 == 0)
		return (TRUE);
	else
		return (FALSE);
}

char	*remove_quote(char *word, int *i)
{
	int		j;
	char	*dest;

	j = 0;
	dest = malloc(sizeof(ft_strlen(word)) + 1);
	if (!dest)
		return (NULL);
	printf("i before %d\n", *i);
	while (word[*i])
		{
			if ((which_quote(word[*i]) && *i == 0) || (which_quote(word[*i])
				&& word[*i + 1] == '\0'))
			{
				printf("char : %c\n", word[*i]);
				(*i)++;
			}
			else
			{
				printf(" cmds word split : %s\n", word);
				dest[j] = word[*i];
				j++;
				(*i)++;
			}
		}
	dest[j] = '\0';
	printf("dest %s\n", dest);
	return (dest);
}

void	quote(t_lexer *lex)
{
	int	i;

	i = 0;
	while (lex)
	{
		i = 0;
		while (lex->word[i])
		{
			if (which_quote(lex->word[i]))
			{
				lex->word = remove_quote( lex->word, &i);
				break ;
			}
			i++;
		}
		lex = lex->next;
	}
}
// void	find_builtin(char *word, t_lexer *lex)
// {
// }