/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:39:48 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/22 14:34:48 by plangloi         ###   ########.fr       */
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
	struct s_lexer	*prev;
	// int				skip;
}					t_lexer;

typedef struct s_env
{
	char			*value;
	char			*key;
	int				index;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

#define IN_REDIR 500 // <
#define HERE_DOC 501 // <<
#define APPEND 502 // >>
#define OUT_REDIR 503 // >
#define PIPE 504 // |

#define S_QUOTE 1 // '
#define D_QUOTE 2 // "

int					which_quote(char input);
int					is_token(char *input, int *i);
int					which_redir(char *input, int *i);
int					count_pipes(t_lexer *lex);