/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/25 11:46:01 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_path(t_env *env, t_cmds *cmds)
{
	int		i;
	char	*path_found;
	char	*path;
	char	**path_env;

	while (env && ft_strnstr(env->key, "PATH", 5) == 0)
		env = env->next;
	if (!env)
		return (NULL);
	path_env = ft_split(env->value, ':');
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

void	ft_cmd_no_found(char *str)
{
	ft_putstr_fd("command not found : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**allocate_env_array(t_shell *shell, int count)
{
	char	**env_array;

	env_array = ft_calloc((count + 1), sizeof(char *));
	if (!env_array)
		exit_and_free(shell, "Error malloc env", 1);
	return (env_array);
}

char	*create_env_entry(char *key, char *value, t_shell *shell)
{
	char	*entry;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		exit_and_free(shell, "Error malloc env", 1);
	entry = ft_strjoin(tmp, value);
	free(tmp);
	if (!entry)
		exit_and_free(shell, "Error malloc env", 1);
	return (entry);
}

int	fill_env_array(t_env *env, char **env_array, t_shell *shell)
{
	t_env	*tmp;
	int		i;
	int		j;

	tmp = env;
	i = 0;
	while (tmp)
	{
		j = 0;
		env_array[i] = create_env_entry(tmp->key, tmp->value, shell);
		if (!env_array[i])
		{
			while (j < i)
			{
				free(env_array[j]);
				j++;
			}
			return (-1);
		}
		tmp = tmp->next;
		i++;
	}
	env_array[i] = NULL;
	return (0);
}

char	**convert_env_to_array(t_env *env, t_shell *shell)
{
	int		count;
	char	**env_array;

	count = count_env_vars(env);
	env_array = allocate_env_array(shell, count);
	if (!env_array)
		return (NULL);
	if (fill_env_array(env, env_array, shell) == -1)
	{
		free(env_array);
		exit_and_free(shell, "Error convert env", 1);
	}
	return (env_array);
}

#include <sys/stat.h>

// Ajoutez cette fonction pour vérifier si le chemin est un répertoire
int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0); // Impossible de récupérer les informations du chemin
	return (S_ISDIR(path_stat.st_mode));
}

void	get_cmds(t_env *env, t_cmds *cmds, t_shell *shell)
{
	char	**env_array;

	if (!cmds || !cmds->tab || !cmds->tab[0])
		exit_and_free(shell, "Invalid command structure", 1);
	env_array = convert_env_to_array(env, shell);
	if (!env_array)
	{
		exit_and_free(shell, "Failed to convert environment", 1);
	}
	if (ft_strchr(cmds->tab[0], '/') != NULL)
	{
		if (is_directory(cmds->tab[0]))
		{
			ft_putstr_fd(cmds->tab[0], STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			free_split(env_array);
			exit_and_free(shell, "", 126);
		}
		else if (access(cmds->tab[0], F_OK | X_OK) == 0)
		{
			cmds->path = ft_strdup(cmds->tab[0]);
		}
	}
	else
	{
		cmds->path = get_path(env, cmds);
	}
	if (!cmds->path)
	{
		ft_cmd_no_found(cmds->tab[0]);
		free_split(env_array);
		exit_and_free(shell, "Command not found", 127);
	}
	execve(cmds->path, cmds->tab, env_array);
	perror("execve");
	free_split(env_array);
	exit_and_free(shell, "Failed to execute command", 126);
}

static void	child_wtermsig(int sig)
{
	int g_return ;
	(void)g_return ;
	g_return = 0;
	if (sig == 2)
	{
		write(1, "\n", 1);
		g_return = 130;
	}
	if (sig == 3)
	{
		write(1, "Quit: 3\n", 8);
		g_return = 131;
	}
}

void	wait_child(t_shell *shell)
{
	int		stat;
	t_cmds	*snake;

	int g_return ;
	(void)g_return ;
	snake = shell->cmds;
	stat = 0;
	while (snake)
	{
		if (snake->pid != -2 && snake->pid != -1)
		{
			waitpid(snake->pid, &stat, 0);
			if (WIFSIGNALED(stat))
				child_wtermsig(WTERMSIG(stat));
			else if (WIFEXITED(stat))
				g_return = WEXITSTATUS(stat);
		}
		snake = snake->next;
	}
}

void	close_all_fds(t_fd *fds)
{
	if (!(fds->pipes[0] == -2) && fds->pipes[0] >= 0)
		close(fds->pipes[1]);
	if (!(fds->pipes[1] == -2) && fds->pipes[1] >= 0)
		close(fds->pipes[1]);
	if (!(fds->redir[0] == -2) && fds->redir[0] >= 0)
		close(fds->redir[0]);
	if (!(fds->redir[1] == -2) && fds->redir[1] >= 0)
		close(fds->redir[1]);
	if (!(fds->output == -2) && fds->output >= 0)
		close(fds->output);
	if (!(fds->input == -2) && fds->input >= 0)
		close(fds->input);
}