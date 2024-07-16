/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:53:16 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/16 15:29:17 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_before_loop(t_cmds **cmds, t_lexer **lex)
{
	free_cmds(cmds);
	free_lexer(lex);
}