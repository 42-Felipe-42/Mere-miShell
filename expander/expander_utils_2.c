/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:45:24 by lmerveil          #+#    #+#             */
/*   Updated: 2024/08/23 12:03:23 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*copy_if_not_quoted(char *input, int *i, int start, char *tmp)
{
	while (input[*i] != '$' && input[*i] != '\'' && input[*i] != '\"'
		&& input[*i] != '\0')
		(*i)++;
	tmp = ft_strndup(input + start, *i - start);
	return (tmp);
}

char	*copy_if_quoted(char *input, int *i, int opened, int start)
{
	char	*tmp;

	tmp = NULL;
	while (opened && input[*i])
	{
		if (opened == which_quote(input[*i]))
			opened = 0;
		(*i)++;
	}
	tmp = ft_strndup(input + start, *i - start);
	return (tmp);
}
