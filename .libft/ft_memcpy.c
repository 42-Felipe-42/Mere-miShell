/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:17:46 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/17 12:53:51 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		(*(unsigned char *)(dest + i) = (*(unsigned char *)(src + i)));
			i++;
	}
	return (dest);
}

/* int main ()
{
	char dest[10];
	char *src = "pilou";
	size_t n = 3;

	printf("%p\n",ft_memcpy(dest, src,n));
	printf("%p\n",memcpy(dest, src,n));
} */