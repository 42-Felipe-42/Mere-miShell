/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:32:17 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/16 16:51:23 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	strlen;
	unsigned int	total_size;
	char			*new;

	if (s == NULL)
		return (NULL);
	total_size = 0;
	strlen = ft_strlen((char *)s);
	if (start > strlen)
		return (ft_strdup(""));
	s = s + start;
	while (s[total_size] && len--)
		total_size++;
	new = malloc(sizeof(char) * (total_size + 1));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, s, total_size + 1);
	return (new);
}
/**
 * Crée une nouvelle sous-chaîne à partir de la chaîne d'origine.
 * s       Chaîne d'origine.
 * start   Position de départ dans la chaîne d'origine.
 * len     Longueur maximale de la sous-chaîne.
 * return  Nouvelle sous-chaîne créée ou NULL en cas d'erreur.
 */