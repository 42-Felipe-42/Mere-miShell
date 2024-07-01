/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:43:22 by lmerveil          #+#    #+#             */
/*   Updated: 2024/07/01 17:43:54 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


void	print_list_lex(t_lexer *shell)
{
	t_lexer	*current_lex;

	current_lex = shell;
	while (current_lex)
	{
		if (current_lex->next == NULL)
		{
			ft_putstr_fd(GREEN "Last Node : ", STDOUT_FILENO);
		}
		else
		{
			ft_putstr_fd(RED "Past Node : ", STDOUT_FILENO);
		}
		ft_putstr_fd(current_lex->word, STDOUT_FILENO);
		printf(RESET "\n");
		ft_putstr_fd(BLUE "TOKEN :", STDOUT_FILENO);
		printf("%d\n" RESET, current_lex->token, STDOUT_FILENO);
		current_lex = current_lex->next;
	}
}
void	print_list_cmds(t_shell *shell)
{
	t_cmds	*current_cmd;
	t_lexer	*redir;

	current_cmd = shell->cmds;
	while (current_cmd)
	{
		redir = current_cmd->lex_redir;
		while (redir)
		{
			ft_putstr_fd(YELLOW "WORD: ", STDOUT_FILENO);
			ft_putstr_fd(redir->word, STDOUT_FILENO);
			ft_putstr_fd("\n" RESET, STDOUT_FILENO);
			printf("TOKEN: %d\n", redir->token);
			redir = redir->next;
		}
		current_cmd = current_cmd->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_lexer	*lex;
	t_shell	*current;
	char	*input;
	t_env	*env;
	t_shell	*shell;
	t_cmds	*cmds;

	lex = NULL;
	(void)ac;
	(void)current;
	shell = malloc(sizeof(t_shell));
	shell->av = ft_strdup(*av);
	input = av[1];
	env = store_env(envp);
	shell->env = env;
	cmds = malloc(sizeof(t_cmds));
	while (1)
	{
		input = ft_readline();
		lex_str(input, &lex);
		expander(lex, env, shell);
		cmds = new_cmds(&lex, &cmds);
		// printf(RED "token %d\n" RESET, lex->token);
		// printf(RED "word %s\n" RESET, lex->word);
		quote(lex);
		// if (lex->token != 0)
		shell->cmds = cmds;
		current = shell;
		// print_list(current);
		// print_list_lex(lex);
		// free(lex);
		print_list_cmds(shell);
	}
	return (0);
}
