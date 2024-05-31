/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:48:27 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/13 11:18:45 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	if (size && (nmemb > __SIZE_MAX__ / size))
		return (NULL);
	dest = malloc(nmemb * size);
	if (!dest)
		return (NULL);
	ft_bzero (dest, nmemb * size);
	return (dest);
}

/* int main()
{
	size_t nb = 3;
	size_t size = 0;

	printf ("%p \n",ft_calloc(nb,size));
	printf ("%p \n",calloc(nb,size));
} */