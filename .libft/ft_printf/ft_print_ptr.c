/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:27:33 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/20 17:11:44 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(long int ptr)
{
	int	count;

	count = 0;
	if (ptr == 0)
		return (ft_print_str("(nil)"));
	count += ft_print_str("0x");
	count += ft_print_hexa(ptr, 'x');
	return (count);
}
