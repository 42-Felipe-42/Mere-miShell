/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:18:29 by louismdv          #+#    #+#             */
/*   Updated: 2024/07/28 23:47:19 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// void	print_list_cmds(t_shell *shell)
// {
// 	t_cmds	*current_cmd;
// 	int		i;
// 	t_lexer	*redir;

// 	current_cmd = shell->cmds;
// 	while (current_cmd)
// 	{
// 		i = 0;
// 		while (current_cmd->tab && current_cmd->tab[i])
// 		{
// 			if (current_cmd->next == NULL)
// 				ft_putstr_fd(GREEN "Last Node tab : ", STDOUT_FILENO);
// 			else
// 				ft_putstr_fd(RED "Past Node tab : ", STDOUT_FILENO);
// 			ft_putstr_fd(current_cmd->tab[i], STDOUT_FILENO);
// 			printf(RESET "\n");
// 			i++;
// 		}
// 		redir = current_cmd->lex_redir;
// 		while (redir)
// 		{
// 			ft_putstr_fd(YELLOW "Redirection: ", STDOUT_FILENO);
// 			ft_putstr_fd(redir->word, STDOUT_FILENO);
// 			printf(" (Token: %d)\n", redir->token);
// 			redir = redir->next;
// 		}
// 		current_cmd = current_cmd->next;
// 	}
// }

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
		printf("\n");
		current = current->next;
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
