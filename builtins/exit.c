/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:05:00 by felipe            #+#    #+#             */
/*   Updated: 2024/07/26 11:28:03 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

// Fonction pour vérifier si la chaîne représente un nombre valide avec signe
static int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-') // gérer les signes
		i++;
	if (str[i] == '\0') // Si seulement un signe, ce n'est pas valide
		return (0);
	while (str[i])
	{
		if (!isdigit(str[i])) // vérifier que tous les caractères restants sont des chiffres
			return (0);
		i++;
	}
	return (1);
}

// Fonction pour gérer les arguments de exit
static int	exit_args(char **tab, int *flag)
{
	if (!tab[1]) // Aucun argument fourni après exit
	{
		return (0); // code de sortie par défaut
	}

	if (!is_valid_number(tab[1]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(tab[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		*flag = 1;
		return (2); // code d'erreur pour argument invalide
	}
	if (tab[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		*flag = 1;
		return (1); // code d'erreur pour trop d'arguments
	}
	return (atoi(tab[1]) % 256); // retourner le code de sortie
}

void	ft_exit(t_shell *shell, t_cmds *cmd, t_fd *fd)
{
	int	flag;
	int	ext;

	flag = 0;
	ext = exit_args(cmd->tab, &flag);
	if (cmd->tab[1] && cmd->tab[2] && !flag)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		shell->exit_code = 1;
		return;
	}
	if (cmd->next || cmd->prev)
		return;
	ft_freeshell(shell);
	close_all_fds(fd);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(ext);
}



