/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:24 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/31 12:28:20 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_all_fds(t_fd *fds)
{
	if (!(fds->pipes[0] == -2) && fds->pipes[0] >= 0)
		close(fds->pipes[0]);
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

void	close_fds_parent(t_fd *fds)
{
	if (fds->input != -2 && fds->input >= 0)
		close(fds->input);
	if (fds->output != -2 && fds->output >= 0)
		close(fds->output);
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

