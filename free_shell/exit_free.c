/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:53:16 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/28 22:46:58 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_before_loop(t_shell *shell)
{
	if (!shell)
		return ;
	free_cmds(&(shell->cmds));
}

void	exit_and_free(t_shell *shell, char *str, int sig)
{
	if (str)
		perror(str);
	if (shell)
		ft_freeshell(shell);
	exit(sig);
}
