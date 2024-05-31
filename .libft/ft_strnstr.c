/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:05:32 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/16 18:51:42 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!s1 && len == 0)
		return (0);
	if (!s2[i])
		return ((char *)s1);
	while (s1[i] && i < len)
	{
			j = 0;
		while (s1[i] && s1[i + j] == s2[j] && ((i + j) < len))
		{	
			if (s2[j + 1] == '\0')
				return ((char *)s1 + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

/* int main()
{
    char s1[] = "Pull up";

    char s2[] = "up";

   
    int n = 7; 

    printf("Chaîne principale: %s\n", s1);

    printf("Sous-chaîne à rechercher: %s\n", s2);

    printf("Nombre maximal de caractères à examiner dans s1: %d\n", n);

    char *result = ft_strnstr(s1, s2, n);

    if (result != NULL)
    {
        printf("Sous-chaîne trouvée à l'indice %ld: %s\n", result - s1, result);
    }
    else
    {
        printf("Sous-chaîne non trouvée.\n");
    }

    return 0;
} */