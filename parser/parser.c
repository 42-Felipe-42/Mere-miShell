/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:12:09 by lmerveil          #+#    #+#             */
/*   Updated: 2024/07/03 16:09:27 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Your shell must implement the following builtins:
// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

void	is_builtin(t_cmds *cmds, t_lexer *lex)
{
	if (ft_strncmp(lex->word, "echo",4) == 0 && ft_strlen(lex->word) == 4)
		cmds->builtin = ECHO;
	else if (ft_strcmp(lex->word, "cd") == 0 && ft_strlen(lex->word) == 2)
		cmds->builtin = CD;
	else if (ft_strcmp(lex->word, "pwd") == 0 && ft_strlen(lex->word) == 3)
		cmds->builtin = PWD;
	else if (ft_strcmp(lex->word, "export") == 0 && ft_strlen(lex->word) == 6)
		cmds->builtin = EXPORT;
	else if (ft_strcmp(lex->word, "unset") == 0 && ft_strlen(lex->word) == 5)
		cmds->builtin = UNSET;
	else if (ft_strcmp(lex->word, "env") == 0 && ft_strlen(lex->word) == 3)
		cmds->builtin = ENV;
	else if (ft_strncmp(lex->word, "exit",4) == 0 && ft_strlen(lex->word) == 4)
		cmds->builtin = EXIT;
}
