/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:29:54 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/07 11:34:06 by plangloi         ###   ########.fr       */
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

void	store_token_words(char *input, t_lexer **lex, int start, int len)
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

void	is_quoted(char *input, int *i, int *opened)
{
	*opened = quote_de_porc(input[*i]);
	(*i)++;
	while (*opened && input[*i])
	{
		if (*opened == quote_de_porc(input[*i]))
			*opened = 0;
		(*i)++;
	}
}

void	is_word(char *input, int *i)
{
	int	temp;

	temp = 0;
	while (input[*i] && input[*i] != ' ' && !find_token(input, *i))
	{
		if (quote_de_porc(input[*i]))
			is_quoted(input, i, &temp);
		else
			(*i)++;
	}
}

void	lex_str(char *input, t_lexer **lex)
{
	int	i;
	int	start;
	int	temp;

	i = 0;
	temp = 0;
	start = 0;
	while (input[i])
	{
		while ((input[i] && input[i] == ' ') || (input[i] >= 7 && input[i] <= 13))
			i++;
		if (input[i] == '\0')
			break ;
		start = i;
		if (quote_de_porc(input[i]))
			is_quoted(input, &i, &temp);
		else
			is_word(input, &i);
		if (i > start)
			store_token_words(input, lex, start, i - start);
		if (find_token(input, i) != FALSE)
			(store_token(lex, find_token(input, i)), i++);
		if (find_token(input, i) == HERE_DOC || find_token(input, i) == APPEND)
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
int main() {
    t_lexer *lex = NULL;
    char input[] = "echo 'hello' > file.txt";

    lex_str(input, &lex);

    // Afficher les tokens pour vérifier
    t_lexer *current = lex;
    while (current) {
        if (current->word) {
            printf("Word: %s\n", current->word);
        } else {
            printf("Token: %c\n", current->token);
        }
        current = current->next;
    }

    // Libérer la mémoire (à implémenter)
    return 0;
}