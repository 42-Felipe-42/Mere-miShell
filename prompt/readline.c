/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:33:39 by lmerveil          #+#    #+#             */
/*   Updated: 2024/06/21 22:32:11 by louismdv         ###   ########.fr       */
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
    return 0;
}
