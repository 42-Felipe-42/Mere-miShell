/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:43:22 by lmerveil          #+#    #+#             */
/*   Updated: 2024/07/05 17:19:20 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// void	print_list_cmds(t_shell *shell)
// {
// 	t_cmds	*current_cmd;
// 	t_lexer	*redir;

// 	current_cmd = shell->cmds;
// 	while (current_cmd)
// 	{
// 		redir = current_cmd->lex_redir;
// 		while (redir)
// 		{
// 			ft_putstr_fd(YELLOW "WORD: ", STDOUT_FILENO);
// 			ft_putstr_fd(redir->word, STDOUT_FILENO);
// 			ft_putstr_fd("\n" RESET, STDOUT_FILENO);
// 			printf(BLUE "TOKEN: %d\n" RESET, redir->token);
// 			redir = redir->next;
// 		}
// 		printf("builtin %d\n", current_cmd->builtin);
// 		current_cmd = current_cmd->next;
// 	}
// }
void	print_list_cmds(t_shell *shell)
{
	t_cmds	*current_cmd;
	int		i;
	t_lexer	*redir;

	current_cmd = shell->cmds;
	while (current_cmd)
	{
		i = 0;
		while (current_cmd->tab && current_cmd->tab[i])
		{
			if (current_cmd->next == NULL)
				ft_putstr_fd(GREEN "Last Node : ", STDOUT_FILENO);
			else
				ft_putstr_fd(RED "Past Node : ", STDOUT_FILENO);
			ft_putstr_fd(current_cmd->tab[i], STDOUT_FILENO);
			printf(RESET "\n");
			i++;
		}
		// Afficher les redirections associées
		redir = current_cmd->lex_redir;
		while (redir)
		{
			ft_putstr_fd(YELLOW "Redirection: ", STDOUT_FILENO);
			ft_putstr_fd(redir->word, STDOUT_FILENO);
			printf(" (Token: %d)\n", redir->token);
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
		cmds->builtin = 0;
		input = ft_readline();
		lex_str(input, &lex);
		expander(lex, shell);
		cmds = create_cmds(lex);
		shell->cmds = cmds;
		shell->lex = lex;
		current = shell;
		parser(shell);
		// print_list(current);
		// print_list_lex(lex);
		// free(lex);
		print_list_cmds(shell);
		
	}
	return (0);
}
