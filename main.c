/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:43:22 by lmerveil          #+#    #+#             */
/*   Updated: 2024/07/29 10:36:09 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	set_struct(t_shell *shell, char **av, char **envp)
{
	shell->av = ft_strdup(av[0]);
	shell->cmds = NULL;
	shell->env = NULL;
	shell->flag = 0;
	get_env(shell, envp);
	shell->lex = NULL;
}

void	free_tokens(t_lexer *lexer)
{
	t_lexer	*temp;

	while (lexer)
	{
		temp = lexer;
		lexer = lexer->next;
		if (temp->word)
			free(temp->word);
		free(temp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_lexer	*lex;
	t_shell	*shell;
	t_cmds	*cmds;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit_and_free(shell, "Error : malloc shell");
	(void)ac;
	set_struct(shell, av, envp);
	while (1)
	{
		lex = lexer(av, shell);
		if (!lex)
			free_lexer(&lex);
		parser(lex, shell);
		cmds = create_cmds(lex, shell);
		shell->cmds = cmds;
		free_lexer(&lex);
		run_exec(shell);
		free_before_loop(shell);
		shell->cmds = NULL;
	}
	return (0);
}
