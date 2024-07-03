/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:54:33 by plangloi          #+#    #+#             */
/*   Updated: 2024/04/17 18:13:04 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char *envp[])
{
	int		fd[2];

	if (argc != 5)
		return (ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n"), 1);
	first_child(argv, fd, envp);
	last_child(argv, argc, fd, envp);
	close(fd[0]);
	close(fd[1]);
	wait_children();
	return (0);
}
