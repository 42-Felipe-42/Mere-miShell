/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:49:39 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/26 14:03:57 by lmerveil         ###   ########.fr       */
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

// char	*remove_quote(char *word, int *i)
// {
// 	int		j;
// 	char	*dest;
// 	j = 0;
// 	dest = malloc(sizeof(ft_strlen(word)) + 1);
// 	if (!dest)
// 		return (NULL);
// 	// printf("i before %d\n", *i);
// 	while (word[*i])
// 		{
// 			if ((which_quote(word[*i]) && *i == 0) || (which_quote(word[*i])
// 				&& word[*i + 1] == '\0'))
// 			{
// 				printf("char : %c\n", word[*i]);
// 				(*i)++;
// 			}
// 			else
// 			{
// 				// printf(" cmds word split : %s\n", word);
// 				dest[j] = word[*i];
// 				j++;
// 				(*i)++;
// 			}
// 		}
// 	dest[j] = '\0';
// 	printf("dest %s\n", dest);
// 	return (dest);
// }

char	*remove_quote(char *word)
{
	char	*dest;

	dest = malloc(sizeof(ft_strlen(word)) + 1);
	if (!dest)
		return (NULL);
	// printf("word[0] : [%c]\n", word[0]);
	// printf("word[ft_strlen] : [%c]\n", word[ft_strlen(word) - 1]);
	if (which_quote(word[0]) && which_quote(word[ft_strlen(word) - 1]))
	{
		dest = ft_strndup(word + 1, ft_strlen(word) - 2);
		dest[ft_strlen(word)] = '\0';
		// printf("dest %s\n", dest);
		return (dest);
	}
	else
		return (word);
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
				lex->word = remove_quote( lex->word);
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

// void    init_cmds(t_cmds **cmds)
// {
//     cmds = malloc(sizeof(t_cmds));
//     if (!cmds)
//         return ;
//     (*cmds)->tab = NULL;
//     (*cmds)->builtin = 0;
//     (*cmds)->lex_word = NULL;
//     (*cmds)->next = NULL;
//     (*cmds)->prev = NULL;
// }
// int    count_lexem(t_lexer *lex)
// {
//     int    count;

//     count = 0;
//     while (lex)
//     {
//         count++;
//         lex = lex->next;
//     }
//     return (count);
// }

// t_cmds    *create_cmds(t_lexer *lex, t_cmds **cmds)
// {
//     t_lexer    *tmp;
//     int        count;
//     int        i;

//     i = 0;
//     count = count_lexem(lex);
//     tmp = lex;
//     (*cmds)->tab = malloc((count + 1) * (sizeof(char *)));
//     while (i < count)
//     {
//         (*cmds)->tab = ft_strdup(lex->word[i]);
//         i++;
//         count--;
//     }
// }

