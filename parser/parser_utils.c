/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:49:39 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/08 14:29:31 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quote_closed(char *word)
{
	int	d_quote;
	int	i;
	int	s_quote;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (word[i])
	{
		if (which_quote(word[i]) == D_QUOTE)
			d_quote++;
		if (which_quote(word[i]) == S_QUOTE)
			s_quote++;
		i++;
	}
	if (s_quote % 2 == 0 || d_quote % 2 == 0)
		return (TRUE);
	else
		return (FALSE);
}

char	*remove_quote(char *word, int *i)
{
	int		j;
	char	*dest;

	j = 0;
	dest = malloc(sizeof(ft_strlen(word)) + 1);
	if (!dest)
		return (NULL);
	while (word[*i])
	{
		if ((which_quote(word[*i]) && *i == 0) || (which_quote(word[*i])
				&& word[*i + 1] == '\0'))
			(*i)++;
		else
		{
			dest[j] = word[*i];
			j++;
			(*i)++;
		}
	}
	dest[j] = '\0';
	return (dest);
}

void	parser(t_shell *shell)
{
	int		i;
	t_lexer	*lexer;

	lexer = shell->lex;
	i = 0;
	syntaxe(lexer);
	while (lexer)
	{
		i = 0;
		is_builtin(shell->cmds, lexer);
		while (lexer->word && lexer->word[i])
		{
			if (which_quote(lexer->word[i]))
			{
				lexer->word = remove_quote(lexer->word, &i);
				break ;
			}
			i++;
		}
		lexer = lexer->next;
	}
}
int	count_lexem(t_lexer *lex)
{
	int	count;

	count = 0;
	while (lex)
	{
		count++;
		lex = lex->next;
	}
	return (count);
}

int	count_pipes(t_lexer *lex)
{
	int	count;

	count = 0;
	while (lex)
	{
		if (lex->token == PIPE)
			count++;
		lex = lex->next;
	}
	return (count);
}

t_cmds	*new_cmds(t_lexer **lex, t_cmds **cmds)
{
	(*cmds)->lex_redir = (*lex);
	if ((*cmds)->lex_redir == NULL)
		return (NULL);
	return (*cmds);
}

void	syntaxe(t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->token == PIPE && (!tmp->next || tmp->next->token == PIPE))
			return (ft_putstr_fd("Pas la bonne syntaxe de pipe\n",
					STDOUT_FILENO));
		if (tmp->token != 0 && (!tmp->next || tmp->next->token != 0))
			return (ft_putstr_fd("Pas la bonne syntaxe de redirection\n",
					STDOUT_FILENO));
		tmp = tmp->next;
	}
}

t_cmds	*init_cmds(void)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	ft_bzero(cmds, sizeof(t_cmds));
	return (cmds);
}

// copie des donnee de lex vers cmds->lex
void	redir_to_cmds(t_lexer *lex, t_cmds **cmds)
{
	t_lexer	*tmp;
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return ;
	new_node->token = lex->token;
	if (lex->next->word)
		new_node->word = ft_strdup(lex->next->word);
	new_node->next = NULL;
	if ((*cmds)->lex_redir == NULL)
	{
		(*cmds)->lex_redir = new_node;
		return ;
	}
	tmp = (*cmds)->lex_redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}
// cat > khiy | cmd2 > file2

t_lexer	*lex_to_cmds(t_lexer *lex, t_cmds **cmds)
{
	t_lexer	*tmp;
	int		count;
	int		i;

	i = 0;
	count = count_pipes(lex) + 1;
	tmp = lex;
	if (cmds == NULL)
		cmds = malloc(sizeof(t_cmds));
	(*cmds)->tab = malloc((count + 1) * (sizeof(char *)));
	while (tmp && tmp->word)
	{
		if (tmp->word)
			(*cmds)->tab[i] = ft_strdup(tmp->word);
		if (!(*cmds)->tab)
			return (NULL);
		i++;
		if (tmp->next && tmp->next->word)
			tmp = tmp->next;
		else
			break;
	}
	(*cmds)->tab[i] = NULL;
	return (tmp);
}

t_cmds	*create_cmds(t_lexer *lex)
{
	t_lexer *tmp;
	t_cmds *cmds;
	t_cmds *current_cmd;
	cmds = init_cmds();

	current_cmd = cmds;
	tmp = lex;
	while (tmp)
	{
		if (tmp->token == IN_REDIR || tmp->token == OUT_REDIR
			|| tmp->token == APPEND)
		{
			redir_to_cmds(tmp, &current_cmd);
		}
		else if (tmp->token == PIPE)
		{
			current_cmd->next = init_cmds();
			current_cmd->next->prev = current_cmd;
			current_cmd = current_cmd->next;
		}
		else if (tmp->next && tmp->next->token != PIPE)
			tmp = lex_to_cmds(tmp, &current_cmd);
		tmp = tmp->next;
	}
	return (cmds);
}
