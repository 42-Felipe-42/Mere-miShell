/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:16:07 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/16 14:49:50 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	cpy;

	cpy = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while (src[i] && i < size -1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (cpy);
}

/* #include <string.h>
int main()
{
char *a = "Yopla";
char b[20];
size_t size = 6;
printf("%ld \n", ft_strlcpy(b,a,size));
printf("%s \n", b);
printf("%ld \n", strlcpy(b,a,size));
} */