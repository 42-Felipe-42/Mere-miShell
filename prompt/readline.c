/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:33:39 by lmerveil          #+#    #+#             */
/*   Updated: 2024/08/02 11:05:48 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_readline(void)
{
	char	*line;

	line = readline(PROMPT_LINE);
	if (line)
	{
		add_history(line);
		return (line);
	}
	return (NULL);
}
