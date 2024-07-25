/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/25 11:13:18 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// chercher dest dans env, si trouve expand, sinon NULL

// obj: parcourir entrée jusqu'à: '_' ou char non alphanum,
// stocker dans 'dest' et comp avec env
// entrée: input sur indice $
// sortie: valeur associée a env
char	*expand(char *input, int i, t_env *envp, t_shell *shell)
{
	char	*dst;
	char	*env;
	int		j;

	dst = ft_calloc(strlen(input) + 1, sizeof(char *));
	if (!dst)
		exit_and_free(shell, "Malloc error expander", 1);
	env = NULL;
	if (input[i] == '$')
		i++;
	j = 0;
	while (input[i] && (ft_isalpha(input[i]) || input[i] == '_'))
	{
		dst[j++] = input[i];
		i++;
	}
	dst[j] = '\0';
	env = find_env(dst, envp);
	if (!env)
		env = ft_strdup("");
	return (free(dst), env);
}

char	*find_pwd(char *str, t_shell *shell)
{
	if (!ft_strncmp(str, "$0", 2) || !ft_strncmp(str, "$0$", 3))
		str = shell->av;
	else
		return (NULL);
	return (str);
}

void	expander(t_lexer *lex, t_shell *shell)
{
	t_lexer	*tmp;
	char	*expanded_word;

	tmp = lex;
	expanded_word = NULL;
	while (tmp)
	{
		if (tmp->word != NULL && tmp->skip == 0 && ft_strchr(tmp->word, '$')
			&& which_quote(tmp->word[0]) == FALSE)
		{
			if (!(tmp->word[0] == '$' && tmp->word[1] == '\0'))
			{
				expanded_word = no_guillemets(tmp->word, shell);
				free(tmp->word);
				tmp->word = expanded_word;
				tmp->skip = 1;
			}
		}
		tmp = tmp->next;
	}
}

// expand first part of the input. ex: $HOME$$HOME s'arrete au 2eme $
char	*initialize_expansion(char *word, int *i)
{
	char	*exp_w;

	if (*i == 0 && ft_isalnum(word[*i]))
	{
		exp_w = ft_strndup_dol(word);
		while (word[*i] != '$' && word[*i])
			(*i)++;
		return (exp_w);
	}
	else
		exp_w = strdup("");
	return (exp_w);
}

char	*expand_variable(char *word, int *i, t_shell *shell, char *exp_w)
{
	int		dols;
	char	*tmp;
	char	*new_exp_w;

	dols = 0;
	while (word[*i] && word[*i] == '$')
	{
		dols++;
		if (word[*i] == '$' && word[*i + 1] == '$')
		{
			new_exp_w = ft_strjoin(exp_w, "$");
			{
				free(exp_w);
				exit_and_free(shell, "error ft_strjoin expander", 1);
			}
			free(exp_w);
			exp_w = new_exp_w;
		}
		else
			break ;
		(*i)++;
	}
	if (!ft_strncmp(word + *i, "$0", 2) || !ft_strncmp(word + *i, "$0$", 3))
	{
		new_exp_w = ft_strjoin(exp_w, find_pwd(word + *i, shell));
		if (!new_exp_w)
		{
			free(exp_w);
			exit_and_free(shell, "error ft_strjoin expander", 1);
		}
		free(exp_w);
		exp_w = new_exp_w;
	}
	if (word[*i] && word[*i] == '$' && word[*i + 1] != '$')
	{
		if (dols % 2 != 0)
			tmp = expand(word, *i, shell->env, shell);
		else
			tmp = ft_strndup_dol(word + *i);
		new_exp_w = ft_strjoin(exp_w, tmp);
		if (!new_exp_w)
		{
			free(exp_w);
			exit_and_free(shell, "error ft_strjoin expander", 1);
		}
		free(exp_w);
		free(tmp);
		exp_w = new_exp_w;
	}
	return (exp_w);
}

// returns expanded word
char	*no_guillemets(char *word, t_shell *shell)
{
	char	*exp_w;
	int		i;
	char	*partial_exp;
	char	*tmp;

	exp_w = ft_strdup("");
	i = 0;
	while (word[i])
	{
		partial_exp = initialize_expansion(word, &i);
		tmp = ft_strjoin(exp_w, partial_exp);
		free(partial_exp);
		free(exp_w);
		exp_w = tmp;
		if (word[i])
		{
			tmp = expand_variable(word, &i, shell, exp_w);
			if (!exp_w)
				free(exp_w);
			exp_w = tmp;
		}
		if (ft_strchr(word + i, '$') == NULL)
			break ;
		i++;
	}
	return (exp_w);
}
