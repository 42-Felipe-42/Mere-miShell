/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:41:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/26 14:00:17 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct	s_cmds
{
    char             **tab;
    int                builtin;
    struct s_lexer    *lex_word;
    struct s_cmds    *next;
    struct s_cmds    *prev;
}                    t_cmds;

int     check_quote_closed(char *word);
char	*find_post(char *word, int *i, char **new_w);
void	quote(t_lexer *lex);