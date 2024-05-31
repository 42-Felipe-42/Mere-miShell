/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:11:30 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/30 10:32:07 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_checkarg(char li, va_list ap)
{
	int	result;

	result = 0;
	if (li == 'c')
		result += ft_print_char(va_arg(ap, int));
	else if (li == 's')
		result += ft_print_str(va_arg(ap, char *));
	else if (li == 'd' || li == 'i')
		result += ft_print_int(va_arg(ap, int));
	else if (li == 'u')
		result += ft_print_usgnint(va_arg(ap, unsigned int));
	else if (li == 'x' || li == 'X')
		result += ft_print_hexa(va_arg(ap, unsigned int), li);
	else if (li == 'p')
		result += ft_print_ptr(va_arg(ap, long int));
	else if (li == '%')
		result += ft_print_char('%');
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!format)
		return (-1);
	va_start (ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += ft_checkarg(format[i +1], ap);
			i++;
		}
		else
		{
			count += write(1, &format[i], 1);
		}
	i++;
	}
	va_end (ap);
	return (count);
}

/* int main() {
    int printed;
	char *str = NULL;
    char *ptr = NULL;

	printed = ft_printf("Hello, %s! %d + %d = %d\n", "World", 5, 7, 5 + 7);
    printed = printf("Hello, %s! %d + %d = %d\n\n", "World", 5, 7, 5 + 7);
    ft_printf("ft_printf len: %d\n", printed);
	printf("printf len: %d\n\n", printed);
	ft_printf("Chaine NULL : \n");
	ft_printf("%d\n",ft_printf("%s", str));	
	printf("%d\n\n",printf("%s", str));
	str = "";
	ft_printf("Chaine vide :\n");
	ft_printf("%d\n",ft_printf("%s", str));	
	printf("%d\n\n",printf("%s", str));
	ft_printf("Valeur 0 :\n");
	ft_printf("%d\n",ft_printf(0));
	printf("%d\n\n",printf(0));
	ft_printf("Pointeur NULL :\n");
    ft_printf("%d\n",ft_printf("%p", ptr));
	printf("%d\n\n",printf("%p", ptr));
	
	return 0;
} */