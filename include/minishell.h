/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:12:08 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/09 14:35:01 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../.libft/libft.h"
# include "exec.h"
# include "lexer.h"
# include "parser.h"
// # include "pipex.h"
# include <readline/history.h>
# include <readline/readline.h>

// colors
# define RESET "\x1B[0m"
# define BLACK "\x1B[30m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"
# define BOLD "\x1B[1m"
# define UNDERLINE "\x1B[4m"

// int g_return_code;
typedef struct s_shell
{
	char	*av;
	t_cmds	*cmds;
	t_env	*env;
	t_lexer	*lex;
}			t_shell;

char		*ft_readline(void);
void		expander(t_lexer *lex, t_shell *shell);
char		*no_guillemets(char *word, t_shell *shell);
char		*ft_strndup_dol(char *s);
void		parser(t_lexer **lex, t_shell *shell);
/****************************************************\
|*************************EXEC***********************|
\****************************************************/
int			get_cmds(t_env *env, t_cmds *cmds);
char		*get_path(t_env *env, t_cmds *cmds);
int			here_doc(t_cmds *cmds);
int			first_child(t_cmds *cmds, t_fd *fd, t_env *envp);
int			last_child(t_cmds *cmds, t_fd *fd, t_env *envp);
int			child_looping(int fd_tmp, t_fd *fd, t_cmds *cmds, t_env *envp);
void		close_fd(t_fd *fd, int file, int who);
void		wait_children(void);
void		exec(t_cmds *cmds, t_env *env /* , t_shell *shell */);
#endif