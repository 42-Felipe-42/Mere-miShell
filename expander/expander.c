/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/04 15:40:16 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand(char *str, int i)
{
	char	*dest;
	char	*env;
	int		j;

	dest = (char *)malloc(strlen(str) + 1);
	env = NULL;
	i++;
	j = 0;
	while (str[i] && ft_isalnum(str[i]))
		dest[j++] = str[i++];
	dest[j] = '\0';
	env = getenv(dest);
	free(dest);
	return (env);
}

char	*find_dollars(char *str)
{
	int	i;

	i = 0;
	bool quote;;
	
	quote = false;
	while(str[i])
	{
		if (str[i] == '\'' && quote == false)
			quote = true;
		else if (str[i] == '\'' && quote == true)
			quote = false;
		else if (str[i] == '$' && quote == false)
		{
			str = expand(str, i);
			// break;
		}
		// else
		// 	printf("%c", str[i]);
	i++;
	}
	printf("\n");
	return (str);
}

int	main(int ac, char **av)
{
	(void) ac;
	char *input = av[1];
	printf("%s", find_dollars(input));
	return (0);
}