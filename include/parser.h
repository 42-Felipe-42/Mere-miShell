/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:41:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/13 14:09:05 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_quote_closed(t_lexer *lex);
void    expander(t_lexer *lex, t_env *envp);
char	*find_post(char *word, int *i);
