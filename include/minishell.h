/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:12:08 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/19 14:54:22 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../.libft/libft.h"
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

// int g_return_code;
typedef struct s_shell
{
	char			*av;
	t_lexer	*lex;
	t_env	*env;
}			t_shell;

char		*ft_readline(void);
void		expander(t_lexer *lex, t_env *envp, t_shell *shell);
char		*no_quote(char *word, int i, t_env *envp);

#endif