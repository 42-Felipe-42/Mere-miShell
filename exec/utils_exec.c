/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/12 18:32:19 by felipe           ###   ########.fr       */
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

int	get_cmds(t_env *env, t_cmds *cmds)
{
	// if (!cmds->tab[0])
	// 	return (ft_cmd_no_found(&cmds->tab[0]), exit(EXIT_FAILURE), 1);
	if (ft_strchr(cmds->tab[0], '/') != NULL && access(cmds->tab[0],
			F_OK | X_OK) == 0)
		cmds->path = ft_strdup(cmds->tab[0]);
	else
	{
		cmds->path = get_path(env, cmds);
		if (!cmds->path)
		{
			ft_cmd_no_found(cmds->tab[0]);
			return (exit(EXIT_FAILURE), 1);
		}
	}
	if (execve(cmds->path, cmds->tab, NULL) == -1)
	{
		ft_cmd_no_found(cmds->tab[0]);
		return (free(cmds->path), exit(EXIT_FAILURE), 1);
	}
	return (EXIT_SUCCESS);
}

void	ft_wait_child(t_shell *shell)
{
	int		status;
	t_cmds	*cmd;

	status = -1;
	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->pid != -2 && cmd->pid != -1)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				shell->exit_code = WEXITSTATUS(status);
			if (errno == EACCES)
				shell->exit_code = 126;
			if (cmd->pid == -1)
				shell->exit_code = 127;
		}
		cmd = cmd->next;
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