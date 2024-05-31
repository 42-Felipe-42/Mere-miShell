/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:34:50 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/13 16:57:57 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dest;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		dest[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

/* int main() {
    const char *s1 = "Bonjour ";
    const char *s2 = "je suis NLE";
    char *joined_string = ft_strjoin(s1, s2);

    if (joined_string) {
        printf("s1 : '%s' et s2 : '%s' =  %s\n",s1,s2, joined_string);
        free(joined_string); 
    } 
    return (0);
}  */