/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:21:12 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/09 10:54:34 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = (unsigned char)c;
			i++;
	}
	return (s);
}

/* int	main(void)
{
	char s[100] = "salut";
	char s2[100] = "salut";

	ft_memset(s, 'a', 0);
	memset(s2, 'a', 0);
	printf("%s\n", s);
	printf("%s", s2);
} */