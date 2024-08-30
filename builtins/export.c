/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:05:00 by felipe            #+#    #+#             */
/*   Updated: 2024/08/23 10:44:01 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int is_valid_llong(const char *str)
 {
    if (*str == '\0') 
        return 0;
    int sign = 1;
    if (*str == '+' || *str == '-') 
	{
        if (*str == '-') {
            sign = -1;
        }
        str++;
    }
    if (*str == '\0')
        return 0; 
    long long value = 0;
    while (*str) 
	{
        if (!ft_isdigit((unsigned char)*str)) 
            return 0; // Non numérique caractère trouvé  
        int digit = *str - '0';
        if (value > (LLONG_MAX - digit) / 10) {
            return 0; // Dépassement de valeur
        }
        value = value * 10 + digit;
        str++;
    }
    value *= sign;
    if (value < LLONG_MIN || value > LLONG_MAX) 
        return 0; // Valeur hors des limites
    return 1; // Nombre valide
}

// Fonction pour verifier si la chaîne représente un nombre valide avec signe
static int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if(is_valid_llong(str) == 0)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// Fonction pour gerer les arguments de exit
static int	exit_args(char **tab, int *flag)
{
	if (!tab[1])
	{
		return (0);
	}
	if (!is_valid_number(tab[1]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(tab[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		*flag = 1;
		return (2);
	}
	return (ft_atoi(tab[1]) % 256);
}

void	ft_exit(t_shell *shell, t_cmds *cmd, t_fd *fd)
{
	int	flag;
	int	ext;

	flag = 0;
	ext = 0;
	if (cmd->tab[1])
		shell->tmpexit_code = exit_args(cmd->tab, &flag);
	if (cmd->tab[1] && cmd->tab[2] && !flag)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		shell->tmpexit_code = 1;
		return ;
	}
	if (!cmd->next || !cmd->prev)
	{
		ext = shell->tmpexit_code;
		ft_freeshell(shell);
		close_all_fds(fd);
		ft_putstr_fd("exit\n", 2);
		exit(ext);
	}
	return ;
}
