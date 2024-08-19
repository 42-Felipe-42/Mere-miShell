/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:06:49 by plangloi          #+#    #+#             */
/*   Updated: 2024/08/01 17:12:54 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_cmds *cmds, t_shell *shell, int fd_output, t_fd *fds)
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
		ft_putstr_fd("pwd: ", STDOUT_FILENO);
		ft_putstr_fd(": invalid option\n", STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(pwd, fd_output);
		ft_putstr_fd("\n", fd_output);
	}
	free(pwd);
	ft_freeshell(shell);
	close_all_fds(fds);
	exit(0);
}
