/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:33:39 by lmerveil          #+#    #+#             */
/*   Updated: 2024/07/11 11:45:50 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_readline()
{
    char *line;

    line = readline(GREEN"➜ "RESET YELLOW);
    printf(RESET);
    if (line)
	{
		add_history(line);
		return (line);
    }
	free(line);
    return NULL;
}
