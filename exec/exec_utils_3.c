/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/28 23:15:22 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static void	child_wtermsig(int sig)
{
	int	g_return;

	(void) g_return;
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
	int		g_return;

	(void)g_return;
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
