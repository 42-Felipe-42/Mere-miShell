/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_usgnint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:58:25 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/20 17:10:24 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_usgnint(unsigned int nb)
{
	unsigned int	count;
	unsigned int	n;

	n = nb;
	count = 0;
	if (nb > 9)
	{
		count += ft_print_usgnint(n / 10);
		count += ft_print_usgnint(n % 10);
	}
	else if (nb <= 9)
		count += ft_print_char(n + '0');
	return (count);
}
