/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:44:45 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/09 15:15:17 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (((*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
		&& i < n))
			return ((*(unsigned char *)(s1 + i)) - (*(unsigned char *)
			(s2 + i)));
		i++;
	}
	return (0);
}

/* int main()
{
	char *s1 = "ogLoLppa";
	char *s2 = "oflppa";
	
	printf("%d \n",ft_memcmp(s1,s2,0));
	printf("%d \n",memcmp(s1,s2,0));

} */