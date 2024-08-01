/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:41:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/08/01 10:13:38 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define ECHO 601
# define CD 602
# define PWD 603
# define EXPORT 604
# define UNSET 605
# define ENV 606
# define EXIT 607

typedef struct s_cmds
{
	char			**tab;
	char			*path;
	int				builtin;
	pid_t			pid;
	struct s_lexer	*lex_redir;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}					t_cmds;

int					check_quote_closed(char *word);
void				is_builtin(t_cmds *cmds);

#endif
