/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:08:12 by plangloi          #+#    #+#             */
/*   Updated: 2024/01/10 16:54:17 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define  FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

int	ft_print_hexa(unsigned long nb, char deci);
int	ft_print_usgnint(unsigned int nb);
int	ft_printf(const char *format, ...);
int	ft_print_ptr(long int ptr);
int	ft_print_str(char *str);
int	ft_print_char(char c);
int	ft_print_int(long nb);

#endif
