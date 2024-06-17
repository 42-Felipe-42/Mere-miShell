/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:39:48 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/17 15:59:53 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERR_QUOTE "Error: Unmatched quotes\n"
#define FALSE 0
#define TRUE 1

typedef struct s_lexer
{
	int				token;
	char			*word;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

#define OUT_REDIR 500 // >
#define APPEND 501 // >>
#define IN_REDIR 502 // <
#define HERE_DOC 503 // <<
#define PIPE 504 // |

#define S_QUOTE 1 // ''
#define D_QUOTE 2 // """

// int		find_token(char *input, int i);
int					which_quote(char input);
void				lex_str(char *input, t_lexer **lex);
void				store_token(t_lexer **lex, int token);
void				store_token_words(char *input, t_lexer **lex, int start,
						int len);
int					is_token(char *input, int *i);
void				add_node(t_env **env, char *value);
char				*expand_pars(char *word, t_env *envp);
char				*find_env(char *dest, t_env *envp);
t_env				*store_env(char **env);