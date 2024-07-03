/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:39:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/04/19 16:42:31 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	usage(void)
{
	ft_printf("Usage : ./pipex_bonus file1 cmd1 cmd2 ... cmdn file2\n");
	ft_printf("Usage : ./pipex_bonus here_doc LIMITER cmd1 cmd2 file2\n");
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	i;
	int	fd_temp;

	i = 3;
	fd_temp = 0;
	if (ac < 5 || (ft_strncmp(av[1], "here_doc", 9) == 0 && ac < 6))
		return (usage(), 1);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		fd[0] = here_doc(av);
	else
		first_child(av, fd, envp);
	while ((i < ac - 2))
		child_looping(fd_temp, fd, av[i++], envp);
	last_child(av, ac, fd, envp);
	close_fd(fd, fd_temp, 0);
	wait_children();
	return (EXIT_SUCCESS);
}
