/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:44:15 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/08 17:58:40 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_fd
{
	int	pipes[2];
	int	redir[2];
	int	input;
	int	output;
}		t_fd;

int		get_cmds(t_env *env, t_cmds *cmds);
char	*get_path(t_env *env, t_cmds *cmds);
t_fd	*here_doc(t_cmds *cmds);
int		first_child(t_cmds *cmds, t_fd *fd, t_env *envp);
int		last_child(t_cmds *cmds, t_fd *fd, t_env *envp);
int		child_looping(int fd_tmp, t_fd *fd, t_cmds *cmds, t_env *envp);
void	close_fd(int *fd, int file, int who);
void	wait_children(void);