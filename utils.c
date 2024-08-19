/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:18:29 by louismdv          #+#    #+#             */
/*   Updated: 2024/08/02 15:02:45 by plangloi         ###   ########.fr       */
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
	t_cmds	*current_cmd;
	int		i;

	current_cmd = head;
	while (current_cmd != NULL)
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
		printf("\n");
		current_cmd = current_cmd->next;
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
		printf("----------\n");
		lexer = lexer->next;
	}
}
