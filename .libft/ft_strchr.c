/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:24:56 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/22 14:11:01 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)

{
	unsigned int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == 0)
			return (NULL);
		i++;
	}
	return ((char *)s + i);
}

/* int main()
{
	const char *s = "plouf";
	int c = 'r';

	char *result = ft_strchr(s, c);
	if (result) {
		printf("%s\n", result);
	} else {
		printf("Character not found\n");
	}
} */