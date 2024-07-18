/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:12:08 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/18 14:57:35 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../.libft/libft.h"
# include "exec.h"
# include "lexer.h"
# include "parser.h"
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

// extern int g_return ;

// int g_return_code;
typedef struct s_shell
{
	char	*av;
	int		exit_code;
	t_cmds	*cmds;
	t_env	*env;
	t_lexer	*lex;

}			t_shell;
/*--------------------LEXER--------------------*/
void		lex_str(char *input, t_lexer **lex, t_shell *shell);
void		store_token(t_lexer **lex, int token, t_shell *shell);
void		store_token_words(char *input, t_lexer **lex, int start, int len,
				t_shell *shell);
void		add_node(t_env **env, char *value, t_shell *shell);
void		lexer(t_lexer **lex, char **av, t_shell *shell);
char		*remove_quote(char *word, int *i, t_shell *shell);
t_cmds		*new_cmds(t_lexer **lex, t_cmds **cmds, t_shell *shell);
t_cmds		*create_cmds(t_lexer *lex, t_shell *shell);
t_lexer		*lex_to_cmds(t_lexer *lex, t_cmds **cmds, t_shell *shell);

/*--------------------PARSER--------------------*/
void		parser(t_lexer *lex, t_shell *shell);
char		*expand(char *input, int i, t_env *envp, t_shell *shell);
t_cmds		*init_cmds(t_shell *shell);
void		syntaxe(t_lexer *lex, t_shell *shell);

/*--------------------ENV--------------------*/
void		store_env(t_shell *shell, char **envp);
void		set_env_key_value(t_shell *shell, t_env *new, char **envp, int i);
void		maj_env_node(t_shell *shell, t_env *new_env_node, char **envp,
				int index);
void		get_env(t_shell *shell, char **envp);
char		*ft_readline(void);
void		expander(t_lexer *lex, t_shell *shell);
char		*no_guillemets(char *word, t_shell *shell);
char		*ft_strndup_dol(char *s);
char		*find_env(char *dest, t_env *envp);

/*--------------------EXEC--------------------*/

int			get_cmds(t_env *env, t_cmds *cmds, t_shell *shell);
char		*get_path(t_env *env, t_cmds *cmds);
int			here_doc(t_cmds *cmds, t_shell *shell);
void		close_all_fds(t_fd *fds);
void		close_fds_parent(t_fd *fds);
void		ft_wait_child(t_shell *shell);
void		ft_exec(t_shell *shell, t_cmds *cmd, t_fd *fd);
void		execute_cmd(t_shell *shell, t_cmds *cmds, t_fd *fds);
void		execute_child(t_shell *shell, t_cmds *cmds, t_fd *fds);
void		init_fd(t_fd *fd);
int			handle_input_redir(t_lexer *redirs, t_cmds *cmd, int fd, t_shell *shell);
int			handle_output_redir(t_lexer *redirs, int fd);
void		process_redirections(t_cmds *cmds, int *fd_in, int *fd_out, t_shell *shell);
void		set_fds(t_fd *fd);
void		run_exec(t_shell *shell);
void		child_builtin(t_shell *shell, t_cmds *cmd, t_fd *fd);
void		wait_child(t_shell *shell);

/*--------------------FREE--------------------*/
void		free_lexer(t_lexer **lex);
void		free_cmds(t_cmds **cmds);
void		free_env(t_env **env);
void		free_shell(t_shell *shell);
void		free_before_loop(t_cmds **cmds);
void		exit_and_free(t_shell *shell, char *str, int sig);

#endif