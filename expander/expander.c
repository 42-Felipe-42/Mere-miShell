/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/18 11:25:23 by plangloi         ###   ########.fr       */
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
	char	*dest;
	char	*env;
	int		j;

	dest = (char *)malloc(strlen(input) + 1);
	if (!dest)
		exit_and_free(shell, "Malloc error expander", 1);
	env = NULL;
	if (input[i] == '$')
		i++;
	j = 0;
	while (input[i] && (ft_isalpha(input[i]) || input[i] == '_'))
	{
		dest[j++] = input[i];
		i += 1;
	}
	dest[j] = '\0';
	env = find_env(dest, envp);
	if (!env)
		env = "", free(dest);
	return (free(dest), env);
}

char	*find_pwd(char *str, t_shell *shell)
{
	if (ft_strncmp(str, "$0", 2) == 0 || ft_strncmp(str, "$0$", 3) == 0)
	{
		str = shell->av;
	}
	else
		return (NULL);
	return (str);
}

void	expander(t_lexer *lex, t_shell *shell)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->word != NULL)
		{
			if (tmp->skip == 0 && ft_strchr(tmp->word, '$')
				&& which_quote(tmp->word[0]) == FALSE)
			{
				if (!(tmp->word[0] == '$' && tmp->word[1] == '\0'))
				{
					tmp->word = no_guillemets(tmp->word, shell);
					tmp->skip = 1;
				}
			}
		}
		tmp = tmp->next;
	}
}

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
	return ("");
}

char	*expand_variable(char *word, int *i, t_shell *shell, char *exp_w)
{
	int		dols;
	char	*tmp;

	dols = 0;
	while (word[*i] && word[*i] == '$')
	{
		dols++;
		if (word[*i] && word[*i] == '$' && word[*i + 1] == '$')
			exp_w = ft_strjoin(exp_w, "$");
		else
			break ;
		(*i)++;
	}
	if (find_pwd(word + *i, shell))
		exp_w = ft_strjoin(exp_w, find_pwd(word + *i, shell));
	if (word[*i] && word[*i] == '$' && word[*i + 1] != '$')
	{
		if (dols % 2 != 0)
			tmp = expand(word, *i, shell->env, shell);
		else
			tmp = ft_strndup_dol(word + *i);
		exp_w = ft_strjoin(exp_w, tmp);
	}
	return (exp_w);
}

char	*no_guillemets(char *word, t_shell *shell)
{
	char	*exp_w;
	int		i;
	int		next_dollar_index;

	exp_w = "";
	i = 0;
	while (word[i])
	{
		exp_w = ft_strjoin(exp_w, initialize_expansion(word, &i));
		if (word[i])
		{
			exp_w = expand_variable(word, &i, shell, exp_w);
		}
		next_dollar_index = ft_strchr(word + i + 1, '$') - word;
		if (next_dollar_index < 0)
			break ;
		i = next_dollar_index;
	}
	return (exp_w);
}
