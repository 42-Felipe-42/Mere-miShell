/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:41:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/03 16:45:23 by lmerveil         ###   ########.fr       */
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

#define ECHO 601
#define CD 602
#define PWD 603
#define EXPORT 604
#define UNSET 605
#define ENV 606
#define EXIT 607

int					check_quote_closed(char *word);
t_cmds				*new_cmds(t_lexer **lex, t_cmds **cmds);
void				syntaxe(t_lexer *lex);
void				is_builtin(t_cmds *cmds, t_lexer *lex);
