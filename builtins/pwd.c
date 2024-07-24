/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:06:49 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/24 22:17:10 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	ft_pwd(t_cmds *cmds, t_shell *shell, int fd_output)
{
	char	*pwd;

	(void)shell;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd: error retrieving current directory: getcwd: \
			cannot access parent directories: No such file or directory");
	}
	else if (cmds->tab[1] && cmds->tab[1][0] == '-')
	{
		ft_putstr_fd("pwd: ", STDERR_FILENO);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		// ft_freeshell(shell);
		// exit(2);
		free(pwd);
	}
	else
	{
		ft_putstr_fd(pwd, fd_output);
		ft_putstr_fd("\n", fd_output);
		free(pwd);
		// ft_freeshell(shell);
		// exit(0);
	}
}
