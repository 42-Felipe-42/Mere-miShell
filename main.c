/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:43:22 by lmerveil          #+#    #+#             */
/*   Updated: 2024/09/02 15:25:08 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int		g_signal = 0;

int	rl_event_dummy(void)
{
	return (1);
}

void	set_struct(t_shell *shell, char **av, char **envp)
{
	shell->av = ft_strdup(av[0]);
	shell->cmds = NULL;
	shell->env = NULL;
	shell->flag = 0;
	shell->exit_code = 0;
	shell->tmpexit_code = 0;
	shell->skip_here = 0;
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
			lex = lexer(shell);
			if (parser(lex, shell))
				free_lexer(&lex);
			if (lex)
			{
				cmds = create_cmds(lex, shell);
				run_exec(shell);
			}
			(free_before_loop(shell), shell->cmds = NULL);
		}
	}
	return (0);
}
