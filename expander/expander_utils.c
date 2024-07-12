/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:04:33 by louismdv          #+#    #+#             */
/*   Updated: 2024/07/12 14:14:41 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// copier la variable d'env dans un liste chainee
// t_env	*store_env(char **env)
// {
// 	t_env	*store_value;
// 	char	*str;
// 	int		i;

// 	str = NULL;
// 	store_value = NULL;
// 	i = 0;
// 	if (!env)
// 		return (0);
// 	while (env[i])
// 	{
// 		str = ft_strdup(env[i]);
// 		if (!str)
// 			return (0);
// 		add_node(&store_value, str);
// 		i++;
// 	}
// 	return (store_value);
// }

//copier chars entre dollars ex: $$HOME$PWD 
char	*ft_strndup_dol(char *s)
{
	int		i;
	char	*dst;

	i = 0;
	if (s[0] == '$')
		i++;
	while (s[i] && s[i] != '$')
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	if (s[0] == '$')
	{
		dst[0] = '$';
		i++;
	}
	while (s[i] && s[i] != '$')
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin_char(const char *str, char c)
{
	size_t	len;
	char	*result;

	len = strlen(str);
	result = (char *)malloc(len + 2);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, len + 2);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}