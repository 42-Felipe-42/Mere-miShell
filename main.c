/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:43:22 by lmerveil          #+#    #+#             */
/*   Updated: 2024/06/14 18:30:27 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_lexer	*lex;
	t_lexer	*current;
	char	*input;
	t_env	*env;

	lex = NULL;
	current = NULL;
	(void)ac;
	input = av[1];
	env = store_env(envp);
	while (1)
	{
		input = ft_readline();
		lex_str(input, &lex);
		// if (check_quote_closed(lex) == FALSE)
		// {
		// 	printf("Quote not closed\n");
		// 	break ;
		// }
		

		expander(lex, env);
		current = lex;
		while (current)
		{
			if (current->word)
				printf(GREEN"Word:[%s]\n"RESET, current->word);
			else
				printf("Token: [%d]\n", current->token);
			current = current->next;
		}
	}
	// Libérer la mémoire (à implémenter)
	return (0);
}
