/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:53:16 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/29 10:46:12 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_before_loop(t_shell *shell)
{
	if (!shell)
		return ;
	free_cmds(&(shell->cmds));
}

void	exit_and_free(t_shell *shell, char *str)
{
	int ext_code;

	if (ft_strcmp(str, "Exit") == 0)
		ft_printf("Exit\n");
	else if (ft_strnstr(str, "Error :", 8))
		shell->exit_code = 1;
	perror(str);
	if (shell)
	{
		ft_freeshell(shell);
	}
	ext_code = shell->exit_code;
	exit(ext_code);
}