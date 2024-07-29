/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:53:16 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/29 11:58:15 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_before_loop(t_shell *shell)
{
	if (!shell)
		return;
	free_cmds(&(shell->cmds));
}

void exit_and_free(t_shell *shell, char *str)
{
	int ext_code;

	if (ft_strcmp(str, "Exit") == 0)
		ft_printf("Exit\n");
	else if (ft_strnstr(str, "Error", 5))
	{
		shell->exit_code = 1;
		perror(str);
	}
	else if (ft_strcmp(str, "") == 0)
		;
	else
		perror(str);
	ext_code = shell->exit_code;
	ft_freeshell(shell);
	exit(ext_code);
}