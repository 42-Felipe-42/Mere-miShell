/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/04/22 14:25:01 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	close_fd(int *fd, int file, int who)
{
	if (fd)
	{
		if (fd[0] != -1 && file != -1 && who == 0)
		{
			close(fd[0]);
			close(file);
		}
		if (fd[1] != -1 && file != -1 && who == 1)
		{
			close(fd[1]);
			close(file);
		}
		if (fd[0] != -1 && fd[1] != -1 && who == 2)
		{
			close(fd[0]);
			close(fd[1]);
		}
	}
	if (fd[0] != -1 && fd[1] != -1 && file != -1 && who == 3)
	{
		close(fd[0]);
		close(fd[1]);
		close(file);
	}
}

char	*get_path(char **envp, char *cmd)
{
	int		i;
	char	*path_found;
	char	*path;
	char	**path_env;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	path_env = ft_split(envp[i] + 5, ':');
	i = -1;
	while (path_env[++i])
	{
		path_found = ft_strjoin(path_env[i], "/");
		if (!path_found)
			return (free_split(path_env), exit(EXIT_FAILURE), NULL);
		path = ft_strjoinandfree(path_found, cmd);
		if (!path)
			return (free_split(path_env), free(path_found), exit(1), NULL);
		if (access(path, F_OK) == 0)
			return (free_split(path_env), path);
		free(path);
	}
	return (free_split(path_env), NULL);
}

void	ft_cmd_no_found(char **str)
{
	ft_putstr_fd("command not found : ", 2);
	ft_putstr_fd(str[0], 2);
	ft_putstr_fd("\n", 2);
}

int	get_cmds(char **envp, char *av)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(av, ' ');
	if (!cmds[0])
		return (ft_cmd_no_found(cmds), free_split(cmds), exit(EXIT_FAILURE), 1);
	if (ft_strchr(cmds[0], '/') != NULL && access(cmds[0], F_OK | X_OK) == 0)
		path = ft_strdup(cmds[0]);
	else
	{
		path = get_path(envp, cmds[0]);
		if (!path)
		{
			ft_cmd_no_found(cmds);
			return (free_split(cmds), exit(EXIT_FAILURE), 1);
		}
	}
	if (execve(path, cmds, envp) == -1)
	{
		ft_cmd_no_found(cmds);
		return (free(path), free_split(cmds), exit(EXIT_FAILURE), 1);
	}
	return (EXIT_SUCCESS);
}

void	wait_children(void)
{
	while (1)
	{
		if (waitpid(-1, NULL, 0) == -1)
			break ;
	}
}
