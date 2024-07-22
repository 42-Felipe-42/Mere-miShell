/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:43:22 by lmerveil          #+#    #+#             */
/*   Updated: 2024/07/22 10:35:21 by plangloi         ###   ########.fr       */
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

void	set_struct(t_shell **shell, t_cmds **cmds, t_lexer **lex, char **av)
{
	*shell = malloc(sizeof(t_shell));
	if (!(*shell))
		exit_and_free(*shell, "Error malloc shell", 1);
	ft_bzero(*shell, sizeof(t_shell));
	(*shell)->av = ft_strdup(*av);
	*cmds = malloc(sizeof(t_cmds));
	if (!(*cmds))
		exit_and_free(*shell, "Error malloc cmds", 1);
	ft_bzero(*cmds, sizeof(t_cmds));
	*lex = malloc(sizeof(t_lexer));
	if (!(*lex))
		exit_and_free(*shell, "Error malloc lexer", 1);
	ft_bzero(*lex, sizeof(t_lexer));
}

int	main(int ac, char **av, char **envp)
{
	t_lexer	*lex;
	t_shell	*shell;
	t_cmds	*cmds;

	(void)ac;
	set_struct(&shell, &cmds, &lex, av);
	get_env(shell, envp);
	while (1)
	{
		lexer(&lex, av, shell);
		parser(lex, shell);
		*cmds = *create_cmds(lex, shell);
		shell->cmds = cmds;
		// print_list_cmds(*shell);
		run_exec(shell);
		free_before_loop(&cmds);
	}
	return (0);
}
