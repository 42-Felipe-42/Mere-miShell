/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:43:22 by lmerveil          #+#    #+#             */
/*   Updated: 2024/07/31 16:17:53 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int		g_signal = 0;

void	set_struct(t_shell *shell, char **av, char **envp)
{
	shell->av = ft_strdup(av[0]);
	shell->cmds = NULL;
	shell->env = NULL;
	shell->flag = 0;
	shell->exit_code = 0;
	get_env(shell, envp);
	shell->lex = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_lexer	*lex;
	t_shell	*shell;
	t_cmds	*cmds;

	if (ac == 1)
	{
		shell = malloc(sizeof(t_shell));
		if (!shell)
			exit_and_free(shell, "Error : malloc shell");
		set_struct(shell, av, envp);
		setup_shell_signals();
		while (1)
		{
			lex = lexer(av, shell);
			if (!lex)
				free_lexer(&lex);
			check_captured_signals(shell);
			parser(lex, shell);
			cmds = create_cmds(lex, shell);
			shell->cmds = cmds;
			free_lexer(&lex);
			run_exec(shell);
			free_before_loop(shell);
			shell->cmds = NULL;
		}
	}
	return (0);
}
