/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:29:54 by plangloi          #+#    #+#             */
/*   Updated: 2024/08/19 14:46:20 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// creat maillon + init elements struct pour stock donnees d'un TOKEN
void	store_token(t_lexer **lex, int token, t_shell *shell)
{
	t_lexer	*new;
	t_lexer	*current;

	new = ft_calloc(1, sizeof(t_lexer));
	if (!new)
		exit_and_free(shell, "Error : malloc  lexer");
	new->token = token;
	new->word = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->skip = 0;
	if (!*lex)
		*lex = new;
	else
	{
		current = *lex;
		while (current->next)
			current = current->next;
		current->next = new;
		new->prev = current;
	}
}

// crea maillon + init elements struct pour stocker donnees d'un WORD
void	store_token_words(char *input, t_lexer **lex, int len, t_shell *shell)
{
	t_lexer	*new;
	t_lexer	*current;

	new = ft_calloc(1, sizeof(t_lexer));
	if (!new)
		exit_and_free(shell, "Error : malloc lexer");
	ft_bzero(new, sizeof(t_lexer));
	new->word = ft_strndup(input, len);
	if (!new->word)
	{
		free(new);
		exit_and_free(shell, "Error : malloc lexer");
	}
	new->next = NULL;
	new->prev = NULL;
	if (!*lex)
		*lex = new;
	else
	{
		current = *lex;
		while (current->next)
			current = current->next;
		current->next = new;
		new->prev = current;
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
			store_token_words(input + start, lex, i - start, shell);
		else
		{
			store_token(lex, is_token(input, &i), shell);
			i++;
		}
	}
}

t_lexer	*lexer(t_shell *shell)
{
	char	*input;
	t_lexer	*lex;

	lex = NULL;
	input = ft_readline();
	if (!input && shell->skip_here == 0)
	{
		exit_and_free(shell, "exit");
	}
	input = expander(input, shell);
	lex_str(input, &lex, shell);
	shell->lex = lex;
	return (lex);
}
