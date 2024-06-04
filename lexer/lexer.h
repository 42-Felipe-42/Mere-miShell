/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:39:48 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/04 13:32:59 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct t_lexer
{
	int i;
	int		token;
	char	*str;
	struct s_lexer *next;
	struct s_lexer *prev;
}			s_lexer;

# define BIGGER 500
# define M_BIGGER 501
# define LOWER 502
# define M_LOWER 503
# define PIPE 504
