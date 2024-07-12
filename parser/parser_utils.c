/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:49:39 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/13 00:52:24 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmds	*init_cmds(void)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	ft_bzero(cmds, sizeof(t_cmds));
	return (cmds);
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

int	count_pipes(t_lexer *lex)
{
	int	count;

	count = 0;
	while (lex)
	{
		if (lex->token == PIPE)
			count++;
		lex = lex->next;
	}
	return (count);
}

void	syntaxe(t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->token == PIPE && (!tmp->next || tmp->next->token == PIPE))
			return (ft_putstr_fd("Pas la bonne syntaxe de pipe\n",
					STDOUT_FILENO));
		if (tmp->token != 0 && (!tmp->next || tmp->next->token != 0))
			return (ft_putstr_fd("Pas la bonne syntaxe de redirection\n",
					STDOUT_FILENO));
		tmp = tmp->next;
	}
}

char	*remove_quote(char *word, int *i)
{
	int j;
	char *dest;

	j = 0;
	dest = malloc(sizeof(ft_strlen(word)) + 1);
	if (!dest)
		return (NULL);
	while (word[*i])
	{
		if ((which_quote(word[*i]) && *i == 0) || (which_quote(word[*i])
				&& word[*i + 1] == '\0'))
			(*i)++;
		else
		{
			dest[j] = word[*i];
			j++;
			(*i)++;
		}
	}
	dest[j] = '\0';
	return (dest);
}