/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:33:39 by lmerveil          #+#    #+#             */
/*   Updated: 2024/07/22 17:25:05 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_readline()
{
    char *line;

    line = readline(GREEN"➜ "RESET);
    if (line)
	{
		add_history(line);
		return (line);
    }
	free(line);
    return NULL;
}
