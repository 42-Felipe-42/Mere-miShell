/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:37:37 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/13 16:10:30 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	lensrc;
	unsigned int	lendest;

	i = 0;
	if (!dest && size == 0)
		return (0);
	lensrc = ft_strlen(src);
	lendest = ft_strlen(dest);
	j = lendest;
	if (size == 0 || size <= lendest)
		return (lensrc + size);
	while (src[i] && (i < size - lendest - 1))
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (lendest + lensrc);
}
/* int main()
{
	char dest[10];
	char *src = "Xavier le S";
	size_t s = 5;

	printf("%ld \n",ft_strlcat(dest,src,s));
} */