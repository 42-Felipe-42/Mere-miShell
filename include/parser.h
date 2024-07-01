/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:41:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/01 15:33:43 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_cmds
{
	int				builtin;
	struct s_lexer	*lex_redir;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}					t_cmds;

int					check_quote_closed(char *word);
char				*find_post(char *word, int *i, char **new_w);
void				quote(t_lexer *lex);
void				lex_to_cmds(t_lexer *lex, t_cmds **cmds);
t_cmds				*init_cmds(t_cmds *cmds);
t_cmds				*new_cmds(t_lexer **lex, t_cmds **cmds);
