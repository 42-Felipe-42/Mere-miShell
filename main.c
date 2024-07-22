/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:43:22 by lmerveil          #+#    #+#             */
/*   Updated: 2024/07/22 16:41:03 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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
				ft_putstr_fd(GREEN "Last Node tab : ", STDOUT_FILENO);
			else
				ft_putstr_fd(RED "Past Node tab : ", STDOUT_FILENO);
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

void	set_struct(t_shell *shell, char **av, char **envp)
{
	char	*pwd;

	pwd = ft_strdup(av[0]);
	shell->env = NULL;
	shell->cmds = NULL;
	shell->av = ft_strdup(pwd);
	free(pwd);
	get_env(shell, envp);
}

void	print_lexer_list(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current != NULL)
	{
		printf("Token: %d\n", current->token);
		printf("Word: %s\n", current->word);
		// printf("Skip: %d\n", current->skip);
		printf("\n");
		current = current->next;
	}
}
int	main(int ac, char **av, char **envp)
{
	t_lexer	*lex;
	t_shell	*shell;
	t_cmds	*cmds;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit_and_free(shell, "Error malloc shell", 1);
	;
	(void)ac;
	set_struct(shell, av, envp);
	while (1)
	{
		lex = lexer(av, shell);
		parser(lex, shell);
		cmds = create_cmds(lex, shell);
		shell->cmds = cmds;
		// print_list_cmds(&shell);
		run_exec(shell);
		free_before_loop(&cmds);
		shell->cmds = NULL;
	}
	return (0);
}
