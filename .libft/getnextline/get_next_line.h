/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:04:22 by plangloi          #+#    #+#             */
/*   Updated: 2024/01/03 11:08:24 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../libft.h"
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

char	*ft_check_line(char *line, int fd);
char	*get_next_line(int fd);
char	*ft_clean_static(char *tampon);
char	*ft_save_line(char *tampon);
#endif