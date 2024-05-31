/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 08:54:32 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/16 18:52:39 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s == NULL || f == NULL)
		return ;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/**
 * 	 Applique la fonction de traitement à chaque caractère de la chaîne.
 *  s  :  Chaîne de caractères à traiter.
 *  f  : Pointeur vers la fonction de traitement prenant 
 *       l'indice et un caractère.
 */