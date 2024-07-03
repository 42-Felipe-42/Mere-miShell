/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:16:28 by plangloi          #+#    #+#             */
/*   Updated: 2024/04/17 15:09:24 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include ".libft/ft_printf/ft_printf.h"
# include ".libft/getnextline/get_next_line.h"
# include ".libft/libft.h"

int		get_cmds(char **envp, char *av);
char	*get_path(char **envp, char *cmd);
int		here_doc(char **av);
int		first_child(char **av, int *fd, char **envp);
int		last_child(char **av, int argc, int *fd, char **envp);
int		child_looping(int fd_tmp, int *fd, char *av, char **envp);
void	close_fd(int *fd, int file, int who);
void	wait_children(void);

#endif
