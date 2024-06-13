/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:36:03 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/13 19:08:04 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_check_line(char *line, int fd)
{
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	temp = malloc(sizeof(char) * BUFFER_SIZE +1);
	if (!temp)
		return (NULL);
	if (!line)
	{
		line = malloc(sizeof(char) * 1);
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	while (!ft_strchr(line, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(line), free(temp), NULL);
		temp[bytes_read] = '\0';
		line = ft_join_free(line, temp);
	}
	return (free(temp), line);
}

char	*ft_clean_static(char *tampon)
{
	int		i;
	int		len;
	char	*new_tampon;

	i = 0;
	len = ft_strlen(tampon);
	while (tampon[i] && tampon[i] != '\n')
		i++;
	if (tampon[i] == '\n')
		new_tampon = ft_strndup(tampon + i + 1, len - i);
	else
		new_tampon = ft_strndup(tampon + i, len - i);
	free (tampon);
	return (new_tampon);
}

char	*ft_save_line(char *tampon)
{
	int		i;
	char	*line;

	i = 0;
	if (!tampon)
		return (NULL);
	while (tampon[i] && tampon[i] != '\n')
		i++;
	if (tampon[i] == '\n')
		line = ft_strndup (tampon, i + 1);
	else
		line = ft_strndup (tampon, i);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*tampon;
	char		*line;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	tampon = ft_check_line(tampon, fd);
	if (!tampon || tampon[0] == 0)
	{
		free(tampon);
		tampon = NULL;
		return (NULL);
	}
	line = ft_save_line(tampon);
	if (!line || line[0] == 0)
		return (free(line), free(tampon), NULL);
	tampon = ft_clean_static(tampon);
	if (tampon && tampon[0] == 0)
	{
		free(tampon);
		tampon = NULL;
	}
	return (line);
}

/* 
# include <fcntl.h>
# include <stdio.h>

int main() {
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    while ((line = get_next_line(fd)) != NULL) {
        printf("Ligne lue : %s\n", line);
        free(line);
    }
    close(fd);
	return 0;
}
 */