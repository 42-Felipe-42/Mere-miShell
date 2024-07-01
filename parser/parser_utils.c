/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:49:39 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/01 15:44:55 by plangloi         ###   ########.fr       */
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
		while (lex->word && lex->word[i])
		{
			if (which_quote(lex->word[i]))
			{
				lex->word = remove_quote(lex->word);
				break ;
			}
			i++;
		}
		lex = lex->next;
	}
}
int	count_lexem(t_lexer *lex)
{
	int	count;

	count = 0;
	while (lex)
	{
		count++;
		lex = lex->next;
	}
	return (count);
}


// void	redir_to_cmds(t_lexer *lex, t_cmds **cmds)
// {
// 	t_lexer	*tmp;
// 	t_lexer	*new_node;

// 	new_node = malloc(sizeof(t_lexer));
// 	if (!new_node)
// 		return ;
// 	new_node->token = lex->token;
// 	// if (new_node->token != 0)
// 	// 	printf(BLUE "token %d\n" RESET, new_node->token);
// 	if (lex->word)
// 		new_node->word = ft_strdup(lex->word);
// 	new_node->next = NULL;
// 	if ((*cmds)->lex_redir == NULL)
// 	{
// 		(*cmds)->lex_redir = new_node;
// 		return ;
// 	}
// 	tmp = (*cmds)->lex_redir;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new_node;
// }

// void	lex_to_cmds(t_lexer *lex, t_cmds **cmds)
// {
// 	t_lexer	*tmp;
// 	int		count;
// 	int		i;

// 	i = 0;
// 	// *cmds = init_cmds(*cmds);
// 	count = count_lexem(lex);
// 	tmp = lex;
// 	if (cmds == NULL)
// 		cmds = malloc(sizeof(t_cmds));
// 	(*cmds)->tab = malloc((count + 1) * (sizeof(char *)));
// 	while (i < count)
// 	{
// 		if (!tmp->word)
// 			tmp = tmp->next;
// 		else
// 		{
// 			(*cmds)->tab[i] = ft_strdup(tmp->word);
// 			if (!(*cmds)->tab)
// 				return ;
// 			tmp = tmp->next;
// 		}
// 		i++;
// 	}
// 	(*cmds)->tab[i] = NULL;
// }

t_cmds	*new_cmds(t_lexer **lex, t_cmds **cmds)
{
	// init_cmds(*cmds);
	(*cmds)->lex_redir = (*lex);
	if ((*cmds)->lex_redir == NULL)
		printf("tester 2\n");
	// redir_to_cmds(lx, cmds);
	// lex_to_cmds(lex, cmds);
	return (*cmds);
}

void	syntaxe(t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->token == PIPE && (!tmp->next || tmp->next->token == PIPE))
			return (ft_putstr_fd("Pas la bonne syntaxe de pipe",
					STDOUT_FILENO));
		if (tmp->token != 0 && (!tmp->next || tmp->token != 0))
			return (ft_putstr_fd("Pas la bonne syntaxe de redirection",
					STDOUT_FILENO));
	}
}
// void    find_builtin(char *word, t_lexer *lex)
// {
// }