/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:43:22 by lmerveil          #+#    #+#             */
/*   Updated: 2024/07/24 14:41:14 by plangloi         ###   ########.fr       */
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

void	print_env_list(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		printf(" %s: %s\n", current->key, current->value);
		current = current->next;
	}
}

void	print_lexer_list(t_cmds *head)
{
	t_cmds	*current;
	int		i;

	current = head;
	while (current != NULL)
	{
		i = 0;
		while (current->tab[i])
		{
			printf("Token: %s\n", current->tab[i]);
			i++;
		}
		// printf("Skip: %d\n", current->skip);
		printf("\n");
		current = current->next;
	}
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

// Fonction pour afficher un maillon de la liste t_lexer
void	print_lexer(t_lexer *lexer)
{
	if (!lexer)
	{
		printf("The lexer list is empty.\n");
		return ;
	}
	while (lexer)
	{
		printf("Token: %d\n", lexer->token);
		if (lexer->word)
			printf("Word: %s\n", lexer->word);
		else
			printf("Word: NULL\n");
		printf("Next: %p\n", (void *)lexer->next);
		printf("Prev: %p\n", (void *)lexer->prev);
		printf("----------\n");
		lexer = lexer->next;
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
	(void)ac;
	set_struct(shell, av, envp);
	while (1)
	{
		lex = lexer(av, shell);
		parser(lex, shell);
		cmds = create_cmds(lex, shell);
		print_lexer(cmds->lex_redir);
		shell->cmds = cmds;
		free_lexer(&lex);
		free_lexer(&cmds->lex_redir);
		run_exec(shell);
		// print_env_list(shell->env);
		free_before_loop(shell);
		shell->cmds = NULL;
		cmds->lex_redir  =  NULL;
		lex =  NULL;
		shell->lex = NULL;
	}
	return (0);
}
