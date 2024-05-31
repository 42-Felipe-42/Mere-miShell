/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:47:52 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/07 14:00:18 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i++;
	}
}

/* 	int main ()
{
	char s[13] = "Ali en furry";
	char s2[13] = "Ali en furry";
bzero(s,1);
ft_bzero(s2,1);

printf("%s\n", s);
printf("%s\n", s2);
} */