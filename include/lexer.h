/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:39:48 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/05 16:48:27 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERR_QUOTE "Error: Unmatched quotes\n"
#define FALSE 0
#define TRUE 1

typedef struct s_lexer
{
	int		token;
	char	*word;
	struct s_lexer *next;
}			t_lexer;

# define OUT_REDIR 500	// >
# define APPEND 501		// >>
# define IN_REDIR 502	// <
# define HERE_DOC 503	// <<
# define PIPE 504		// |
