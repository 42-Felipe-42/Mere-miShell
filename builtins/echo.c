/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:03:19 by lmerveil          #+#    #+#             */
/*   Updated: 2024/09/02 11:16:56 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_line(char **tab, int *flag)
{
	int	n;
	int	i;

	n = 1;
	while (tab[n] && tab[n][0] == '-' && tab[n][1] == 'n')
	{
		i = 1;
		if (tab[n][0] == '-' && tab[n][1] == 'n')
		{
			while (tab[n][i] == 'n')
				i++;
			if (tab[n][i] != '\0')
				return (n);
		}
		*flag = 1;
		n++;
	}
	return (n);
}

void	ft_echo(t_shell *shell, t_cmds *cmd, int fd_output, t_fd *fds)
{
	int	i;
	int	flag;
	int	ext;

	flag = 0;
	i = check_line(cmd->tab, &flag);
	if (cmd->tab[1])
	{
		while (cmd->tab[i])
		{
			if (cmd->tab[i] && !cmd->tab[i + 1])
				ft_putstr_fd(cmd->tab[i], fd_output);
			else if (cmd->tab[i])
			{
				(ft_putstr_fd(cmd->tab[i], fd_output));
				if (cmd->spaces[i] == 1)
					ft_putstr_fd(" ", fd_output);
			}
			i++;
		}
	}
	if (!flag || !cmd->tab[1])
		ft_putstr_fd("\n", fd_output);
	ext = shell->exit_code;
	(ft_freeshell(shell), close_all_fds(fds), exit(ext));
}
