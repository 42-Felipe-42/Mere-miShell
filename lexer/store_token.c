/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:29:54 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/06 16:00:04 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	store_token(t_lexer **lex, int token)
{
	t_lexer	*new;
	t_lexer	*current;

	new = ft_calloc(1, sizeof(t_lexer));
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

void	store_token_words(char *input, t_lexer **lex, int start,int len)
{
	t_lexer	*new;
	t_lexer	*current;

	new = ft_calloc(1, sizeof(t_lexer));
	new->word = ft_strndup(input + start, len);
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

void	is_quoted(char *input,int *i, int *opened)
{
	*opened = quote_de_porc(input[*i]);
	(*i)++;
	while(*opened && input[*i])
		
	
}
void	lex_str(char *input, t_lexer **lex)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (find_token(input, i) != FALSE)
			store_token(lex, find_token(input, i));
		if (find_token(input, i) == FALSE)
			store_token_words(input, lex);
		if (find_token(input, i) == HERE_DOC || find_token(input, i) == APPEND)
			i++;
		i++;
	}
}

void	print_lex_list(t_lexer *lex)
{
	t_lexer	*current;

	current = lex;
	while (current)
	{
		if (current->word)
			printf("Word: %s\n", current->word);
		else
			printf("Token: %d\n", current->token);
		current = current->next;
	}
}

int	main(void)
{
	t_lexer *lex = NULL;
	char input[] = "e > ";

	lex_str(input, &lex);
	print_lex_list(lex);

	// Libération de la mémoire (à faire)
	return (0);
}