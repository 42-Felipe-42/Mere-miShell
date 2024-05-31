/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:31:19 by plangloi          #+#    #+#             */
/*   Updated: 2024/02/01 16:25:55 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_countwords(char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words +1);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = -1;
	if (!s)
		return (NULL);
	dest = ft_calloc((ft_countwords(s, c)), sizeof(char *));
	while (++j < ft_countwords(s, c) - 1)
	{
		while (s[i] && s[i] == c)
			i++;
		len = 0;
		while (s[i] && s[i] != c)
		{
			len++;
			i++;
		}
		dest[j] = ft_strndup(((char *)s + i - len), len);
		if (!dest[j])
			return (free_split(dest), NULL);
	}
	return (dest);
}
