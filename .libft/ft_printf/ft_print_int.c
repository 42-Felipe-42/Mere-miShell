/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:20:15 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/28 10:55:49 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_int(long nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		count = write(1, "-2147483648", 11);
		return (count);
	}
	if (nb < 0)
	{
		count += ft_print_char('-');
		count += ft_print_int(nb * -1);
	}
	else if (nb > 9)
	{
		count += ft_print_int(nb / 10);
		count += ft_print_int(nb % 10);
	}
	else if (nb < 10)
		count += ft_print_char(nb + 48);
	return (count);
}
