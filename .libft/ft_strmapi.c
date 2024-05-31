/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:19:05 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/17 12:26:09 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	dest = malloc(ft_strlen(s) +1 * sizeof(char));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = (*f)(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* 
 char my_func(unsigned int i, char str)
 {
 	printf(" %d, %c\n", i, str);
 	return str - 32;
 }

 int main()
 {
	char str[] = "salut";
 	printf("Resultat avant mapi : %s\n", str);
	char *result = ft_strmapi(str, my_func);
	printf("Resultat apres mapi : %s\n", result);
	return 0;
 }
 */