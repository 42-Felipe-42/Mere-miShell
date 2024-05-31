/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:30:55 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/16 16:55:17 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char const *set, int c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*dest;

	start = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[start] && check_set(set, s1[start]))
		start++;
	while (check_set(set, s1[end - 1]) && end > start)
		end--;
	dest = malloc(sizeof(char) * (end - start + 1));
	if (dest == NULL )
		return (NULL);
	ft_strlcpy(dest, s1 + start, end - start +1);
	return (dest);
}

/* int main() {
    const char *s1 = "";
    const char *set = "   xxx   xxx" " x";

    printf("Chaine non trimee : \"%s\"\n", s1);

    char *trimmed = ft_strtrim(s1, set);

    if (trimmed != NULL) {
        printf("Chaine trimee : \"%s\"\n", trimmed);
        free(trimmed);
    } 
    else
	{
		 printf("\n");
	}
	return 0;
}

 */
