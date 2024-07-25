/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:03:19 by lmerveil          #+#    #+#             */
/*   Updated: 2024/07/25 10:57:24 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_newline(char **tab, int *flag)
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

void	ft_echo(t_shell *shell, t_cmds *cmd)
{
	int i;
	int flag;
	// int ext;
	flag = 0;
	(void)shell;
	i = check_newline(cmd->tab, &flag);
	if (cmd->tab[1])
	{
		while (cmd->tab[i])
		{
			if (cmd->tab[i] && !cmd->tab[i + 1])
				printf("%s", cmd->tab[i++]);
			else if (cmd->tab[i])
				printf("%s ", cmd->tab[i++]);
		}
	}
	if (!flag)
		printf("\n");
	// if (cmd->next)
	// 	ext = shell->excode;
	// else
	// 	ext = shell->tmpexcode;
}