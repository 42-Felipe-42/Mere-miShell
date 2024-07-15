/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:39:29 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/15 16:38:09 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_child(t_cmds *cmds, t_fd *fds, t_env *env)
{
	if (fds->pipes[0] != -2)
		close(fds->pipes[0]); // Ferme le descripteur d'entrée du pipe
	if (fds->input != -2)
	{
		if (dup2(fds->input, STDIN_FILENO) == -1)
		{
			perror("dup2 child input");
			close_all_fds(fds);
			// exit(1);
		}
		close(fds->input); // Ferme le descripteur d'entrée
	}
	if (fds->output != -2)
	{
		if (dup2(fds->output, STDOUT_FILENO) == -1)
		{
			perror("dup2 child output");
			close_all_fds(fds);
			// exit(1);
		}
		close(fds->output); // Ferme le descripteur de sortie
	}
	close_all_fds(fds); // Ferme tous les descripteurs restants
	get_cmds(env, cmds);
}
void	execute_cmd(t_shell *shell, t_cmds *cmds, t_fd *fds, t_env *env)
{
	(void)shell;
	cmds->pid = fork();
	if (cmds->pid == -1)
	{
		perror("fork");
		close_all_fds(fds);
		exit(1); // Échec du fork
	}
	if (cmds->pid == 0)
	{ // Processus enfant
		if (cmds->builtin)
		{
			// run_builtins(shell, cmds, fds, 1); // Exécute la commande interne
			close_all_fds(fds);
			exit(0); // Termine le processus enfant après l'exécution du builtin
		}
		else
			execute_child(cmds, fds, env);
// Exécute une commande externe
	}
	close_fds_parent(fds);
	// Ferme les descripteurs inutiles dans le processus parent
	// fds->input = fds->pipes[0]; // Met à jour le descripteur d'entrée du pipe
	fds->redir[0] = fds->pipes[0];
}
// void	ft_exec(t_shell *shell, t_cmds *cmd, t_fd *fd)
// {
// 	// if (cmd->builtin == EXIT)
// 	// 	ft_exit(shell, cmd, fd);
// 	// else if (cmd->builtin == CD)
// 	// 	ft_cd(shell, cmd);
// 	// else if (cmd->builtin == EXPORT)
// 	// 	ft_export(shell, cmd);
// 	// else if (cmd->builtin == UNSET)
// 	// 	ft_unset(shell, cmd);
// 	{
// 		cmd->pid = fork();
// 		// if (cmd->pid == -1)
// 		// 	exitmsg(shell, "fork");
// 		if (cmd->pid == 0)
// 		{
// 			if (cmd->builtin != 0)
// 				child_builtin(shell, cmd, fd);
// 			else
// 				execute_child(cmd, fd, shell->env);
// 		}
// 		close_fds_parent(fd);
// 		fd->redir[0] = fd->pipes[0];
// 	}
// }

void	close_fds_parent(t_fd *fds)
{
	if (fds->input != -2 && fds->input >= 0)
		close(fds->input);
	if (fds->output != -2 && fds->output >= 0)
		close(fds->output);
}
void	run_exec(t_shell *shell)
{
	t_cmds	*tmp_cmd;
	t_fd	fds;

	fds.input = -2;
	tmp_cmd = shell->cmds;
	while (tmp_cmd)
	{
		init_fd(&fds);
		if (tmp_cmd->next)
			if (pipe(fds.pipes) == -1)
				exit(1);
		// exitmsg(shell, "pipe");
		set_redir(tmp_cmd, &fds);
		// if (shell->excode == 130)
		// 	break ;
		printf(RED "fd redir[0] %d \n", fds.redir[0]);
		printf("fd redir[1] %d\n", fds.redir[1]);
		printf("fd input %d \n", fds.input);
		printf("fd output %d\n" RESET, fds.output);
		set_fds(&fds);
		printf("--------AFTER------\n");
		printf(GREEN "fd redir[0] %d \n", fds.redir[0]);
		printf("fd redir[1] %d\n", fds.redir[1]);
		printf("fd input %d \n", fds.input);
		printf("fd output %d\n" RESET, fds.output);
		if (tmp_cmd->tab &&tmp_cmd->tab[0])
			execute_cmd(shell, tmp_cmd, &fds, shell->env);
		if (!tmp_cmd->next)
			close_fds_parent(&fds);
		tmp_cmd = tmp_cmd->next;
	}
	(wait_child(shell), close_all_fds(&fds));
}
