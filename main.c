/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:43:22 by lmerveil          #+#    #+#             */
/*   Updated: 2024/07/12 19:25:36 by felipe           ###   ########.fr       */
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
int	main(int ac, char **av, char **envp)
{
	t_lexer	*lex;
	char	*input;
	t_shell	*shell;
	t_cmds	*cmds;

	lex = NULL;
	(void)ac;
	shell = malloc(sizeof(t_shell));
	shell->av = ft_strdup(*av);
	input = av[1];
	get_env(shell, envp);
	cmds = malloc(sizeof(t_cmds));
	while (1)
	{
		cmds->builtin = 0;
		input = ft_readline();
		lex_str(input, &lex);
		expander(lex, shell);
		parser(lex);
		cmds = create_cmds(lex);
		shell->cmds = cmds;
		shell->lex = lex;
		run_exec(shell);
		print_list_cmds(shell);
		free(shell);
		free(cmds);
		free_split(cmds->tab);
	}
	return (0);
}
