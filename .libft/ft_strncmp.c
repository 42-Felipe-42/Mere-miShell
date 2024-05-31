/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:08:41 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/16 18:52:51 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n -1 && (s1[i] == s2[i]) && s1[i])
		i++;
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}

/* int main() {
    const char *str1 = "Made in Fil";
    const char *str2 = "Made in Phil";
    size_t n = 5;

    int result = ft_strncmp(str1, str2, n);

    if (result == 0) {
        printf("Les deux chaines sont egales jusqu'aux %lu 
		premiers caracteres.\n", n);
    } else if (result < 0) {
        printf("La premiere chaine est inférieure à la deuxieme 
		
		jusqu'au caractere %lu.\n", n);
    } else {
        printf("La premiere chaine est superieure à la deuxieme 
		jusqu'au caractere %lu.\n", n);
    }

    return 0;
} */