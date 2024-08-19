/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:47:49 by felipe            #+#    #+#             */
/*   Updated: 2024/08/01 17:13:13 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_shell *shell, t_cmds *cmd, int fd_output, t_fd *fds)
{
	t_env	*env;

	if (cmd->tab[1])
	{
		perror(cmd->tab[1]);
		ft_freeshell(shell);
		exit(127);
	}
	env = shell->env;
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, fd_output);
			ft_putstr_fd("=", fd_output);
			ft_putstr_fd(env->value, fd_output);
			ft_putstr_fd("\n", fd_output);
		}
		env = env->next;
	}
	ft_freeshell(shell);
	close_all_fds(fds);
	exit(0);
}
