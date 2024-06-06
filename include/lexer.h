/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:39:48 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/06 11:27:30 by plangloi         ###   ########.fr       */
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

#define OUT_REDIR 500 // >
#define APPEND 501 // >>
#define IN_REDIR 502 // <
#define HERE_DOC 503 // <<
#define PIPE 504 // |

int		find_token(char *input, int i);
int		quote_de_porc(char input);
void	store_token(t_lexer **lex, int token);
void	store_token_words(char *input, t_lexer **lex);
void	lex_str(char *input, t_lexer **lex);