/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:49:39 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/02 11:29:35 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tmp_is_token(t_cmds **current_cmd, t_shell *shell)
{
	(*current_cmd)->next = init_cmds(shell);
	(*current_cmd)->next->prev = *current_cmd;
	*current_cmd = (*current_cmd)->next;
}

int	count_arg(t_lexer *lex)
{
	int	count;

	count = 1;
	while (lex && lex->next && lex->next->token != PIPE)
	{
		count++;
		lex = lex->next;
	}
	return (count);
}

int	syntaxe(t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = lex;
	if (tmp && tmp->token == PIPE)
		return (printf("Error : syntax error near unexpected token\n"), 1);
	while (tmp)
	{
		if (tmp->token == PIPE && (!tmp->next || tmp->next->token == PIPE))
			return (printf("Error : syntax error near unexpected token\n"), 1);
		if ((tmp->token != 0 && tmp->token != PIPE) && ((tmp->next == NULL)
				|| (tmp->next->token != 0)))
			return (printf("Error : syntax error near unexpected token\n"), 1);
		tmp = tmp->next;
	}
	return (0);
}

char	*remove_quotes(char *str, t_shell *shell)
{
	int		length;
	int		start;
	int		end;
	char	*result;

	length = ft_strlen(str);
	start = 0;
	end = length - 1;
	if ((str[start] == '\'' && str[end] == '\'') || (str[start] == '\"'
			&& str[end] == '\"'))
	{
		start++;
		end--;
	}
	result = (char *)malloc((end - start + 2) * sizeof(char));
	if (!result)
		exit_and_free(shell, "ERROR : malloc");
	ft_strncpy(result, str + start, end - start + 1);
	result[end - start + 1] = '\0';
	return (result);
}
