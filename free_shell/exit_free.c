/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:53:16 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/24 11:19:21 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_before_loop(t_shell *shell)
{
	if (shell->cmds)
		{printf("test cmds\n");
			free_cmds(&shell->cmds);}
}

void exit_and_free(t_shell *shell, char *str, int sig)
{
    if (str)
        perror(str);
    if (shell)
        free_shell(shell);
    exit(sig);
}