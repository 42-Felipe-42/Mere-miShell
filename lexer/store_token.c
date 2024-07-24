/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:29:54 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/24 10:33:35 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// creation maillon pour stocker donnees d'un TOKEN
void	store_token(t_lexer **lex, int token, t_shell *shell)
{
	t_lexer	*new;
	t_lexer	*current;

	new = ft_calloc(1, sizeof(t_lexer));
	if (!new)
		exit_and_free(shell, "Malloc error lexer", 1);
	new->word = NULL;
	new->token = token;
	if (!*lex)
	{
		*lex = new;
		new->next = NULL;
	}
	else
	{
		current = *lex;
		while (current->next)
			current = current->next;
		current->next = new;
		new->next = NULL;
	}
}

// creation maillon pour stocker donnees d'un WORD
void	store_token_words(char *input, t_lexer **lex, int start, int len,
		t_shell *shell)
{
	t_lexer	*new;
	t_lexer	*current;

	new = ft_calloc(1, sizeof(t_lexer));
	if (!new)
		exit_and_free(shell, "Malloc error lexer", 1);
	new->word = ft_strndup(input + start, len);
	if (!new->word)
	{
		free(new->word); // Free the allocated lexer node if ft_strndup fails
		exit_and_free(shell, "Malloc error lexer word", 1);
	}
	new->token = 0;
	if (!*lex)
	{
		*lex = new;
		new->next = NULL;
	}
	else
	{
		current = *lex;
		while (current->next)
			current = current->next;
		current->next = new;
		new->next = NULL;
	}
}

// parcour le input du premier au dernier quote identique
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
// parcour input en i tant que diff token
void	is_word(char *input, int *i)
{
	while (input[*i] && input[*i] != ' ' && which_redir(input, i) == FALSE
		&& !which_quote(input[*i]))
	{
		(*i)++;
	}
}

// stockage de input[i] en fonction de sa valeur, token ou word
void	lex_str(char *input, t_lexer **lex, t_shell *shell)
{
	int	i;
	int	start;

	i = 0;
	while (input[i])
	{
		while ((input[i] && input[i] == ' ') || (input[i] >= '\a'
				&& input[i] <= '\r'))
			i++;
		if (input[i] == '\0')
			break ;
		start = i;
		if (which_quote(input[i]))
			is_quoted(input, &i, &(int){0});
		else
			is_word(input, &i);
		if (i > start)
			store_token_words(input, lex, start, i - start, shell);
		else
		{
			store_token(lex, is_token(input, &i), shell);
			i++;
		}
	}
}

t_lexer	*lexer(char **av, t_shell *shell)
{
	char	*input;
	t_lexer	*lex;

	lex = NULL;
	input = av[1];
	input = ft_readline();
	if (input == NULL)
		exit_and_free(shell, "Exit", 1);
	lex_str(input, &lex, shell);
	return (lex);
}
