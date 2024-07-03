/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:17:49 by plangloi          #+#    #+#             */
/*   Updated: 2024/04/19 17:27:38 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	child_looping(int fd_tmp, int *fd, char *av, char **envp)
{
	pid_t	pid;

	fd_tmp = fd[0];
	if (pipe(fd) == -1)
		return (close_fd(fd, fd_tmp, 3), exit(EXIT_FAILURE), 1);
	pid = fork();
	if (pid == -1)
		return (close_fd(fd, fd_tmp, 3), exit(EXIT_FAILURE), 1);
	else if (pid == 0)
	{
		if (dup2(fd_tmp, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO)
			== -1)
			return (perror("dup2"), close_fd(fd, fd_tmp, 3), exit(EXIT_FAILURE),
				1);
		close_fd(fd, fd_tmp, 3);
		get_cmds(envp, av);
	}
	close_fd(fd, fd_tmp, 1);
	return (0);
}

int	first_child(char **av, int *fd, char **envp)
{
	pid_t	pid;
	int		infile;

	if (pipe(fd) == -1)
		return (close(fd[0]), close(fd[1]), exit(EXIT_FAILURE), 1);
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), exit(EXIT_FAILURE), 1);
	if (pid == 0)
	{
		infile = open(av[1], O_RDONLY, 0644);
		if (infile == -1)
			return (perror(av[1]), close_fd(fd, infile, 2), exit(EXIT_FAILURE),
				1);
		if (dup2(infile, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO)
			== -1)
			return (perror("dup2"), close_fd(fd, infile, 3), exit(EXIT_FAILURE),
				1);
		close_fd(fd, infile, 3);
		get_cmds(envp, av[2]);
	}
	return (close(fd[1]), 1);
}

int	last_child(char **av, int ac, int *fd, char **envp)
{
	int		outfile;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (exit(EXIT_FAILURE), 1);
	if (pid == 0)
	{
		if (ft_strncmp(av[1], "here_doc", 9) == 0)
			outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
		{
			return (perror(av[ac - 1]), close_fd(fd, outfile, 2),
				exit(EXIT_FAILURE), 1);
		}
		if (dup2(outfile, STDOUT_FILENO) == -1 || dup2(fd[0], STDIN_FILENO)
			== -1)
			return (perror("dup2"), exit(EXIT_FAILURE), 1);
		close_fd(fd, outfile, 3);
		get_cmds(envp, av[ac - 2]);
	}
	return (0);
}

void	loop_here_doc(char **av, int fd)
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(av[2], "\n");
	while (1)
	{
		ft_putstr_fd("here_doc> ", 2);
		line = get_next_line(0);
		if (line == NULL || ft_strncmp(line, limiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(limiter);
}

int	here_doc(char **av)
{
	char	*file_name;
	int		infile;
	int		fd;

	file_name = ft_strdup("42");
	while (access(file_name, F_OK) == 0)
		file_name = ft_strjoinandfree(file_name, "42");
	infile = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (infile == -1)
	{
		perror("infile");
		exit(EXIT_FAILURE);
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("fd");
		exit(EXIT_FAILURE);
	}
	unlink(file_name);
	loop_here_doc(av, infile);
	free(file_name);
	close(infile);
	return (fd);
}
