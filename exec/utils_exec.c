/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/08 17:58:50 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	*get_path(t_env *env, t_cmds *cmds)
{
	int		i;
	char	*path_found;
	char	*path;
	char	**path_env;

	while (env && ft_strnstr(env->value, "PATH=", 5) == 0)
		env = env->next;
	if (!env)
		return (NULL);
	
	path_env = ft_split(env->value + 5, ':');
	i = -1;
	while (path_env[++i])
	{
		path_found = ft_strjoin(path_env[i], "/");
		if (!path_found)
			return (free_split(path_env), exit(EXIT_FAILURE), NULL);
		path = ft_join_free(path_found, cmds->tab[0]);
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

int	get_cmds(t_env	*env, t_cmds *cmds)
{
	if (!cmds->tab[0])
		return (ft_cmd_no_found(cmds->tab[0]), exit(EXIT_FAILURE), 1);
	if (ft_strchr(cmds->tab[0], '/') != NULL && access(cmds->tab[0], F_OK | X_OK) == 0)
		cmds->path = ft_strdup(cmds->tab[0]);
	else
	{
		cmds->path = get_path(env, cmds->tab[0]);
		if (!cmds->path)
		{
			ft_cmd_no_found(cmds->tab[0]);
			return (exit(EXIT_FAILURE), 1);
		}
	}
	if (execve(cmds->path, cmds->tab[0], env) == -1)
	{
		ft_cmd_no_found(cmds);
		return (free(cmds->path), exit(EXIT_FAILURE), 1);
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
