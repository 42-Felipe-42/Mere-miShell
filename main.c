/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:43:22 by lmerveil          #+#    #+#             */
/*   Updated: 2024/06/17 16:02:23 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	print_list(t_shell *shell)
{
	while (shell->lex)
	{
		printf(GREEN"Word : [%s]\n"RESET, shell->lex->word);
		shell->lex = shell->lex->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_lexer	*lex;
	t_lexer	*current;
	char	*input;
	t_env	*env;
	t_shell	*shell;

	lex = NULL;
	(void)ac;
	shell = malloc(sizeof(t_shell));
	env = NULL;
	shell->av = ft_strdup(*av);
	input = av[1];
	env = store_env(envp);
	shell->env = env;
	while (1)
	{
		input = ft_readline();
		lex_str(input, &lex);
		expander(lex, env, shell);
		shell->lex = lex;
		current = shell->lex;
		print_list(shell);
	}
	return (0);
}
