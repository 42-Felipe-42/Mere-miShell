/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/08/19 16:38:47 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// chercher dest dans env, si trouve expand, sinon NULL

// obj: parcourir entrée jusqu'à: '_' ou char non alphanum,
// stocker dans 'dest' et comp avec env
// entrée: input sur indice $
// sortie: valeur associée a env
char	*expand(char *input, int i, t_shell *shell)
{
	char	*dst;
	char	*env;
	int		j;

	dst = ft_calloc(ft_strlen(input) + 1, sizeof(char *));
	if (!dst)
		exit_and_free(shell, "Error : Malloc expander");
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
	env = find_env(dst, shell->env);
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

// expand first part of the input. ex: $HOME$$HOME s'arrete au 2eme $
char	*initialize_expansion(char *word, int *i)
{
	char	*exp_w;

	if (*i == 0 && word[*i] != '\0' && (ft_isalnum(word[*i])
			|| init_exp_checks(word, *i)))
	{
		exp_w = ft_strndup_dol(word);
		while (word[*i] != '$' && word[*i])
			(*i)++;
		return (exp_w);
	}
	else
		exp_w = ft_strdup("");
	return (exp_w);
}

// returns expanded word
char	*no_guillemets(char *word, int *i, t_shell *shell)
{
	char	*exp_w;
	char	*partial_exp;
	char	*tmp;

	exp_w = ft_strdup("");
	partial_exp = initialize_expansion(word, i);
	exp_w = join_and_free(exp_w, partial_exp, shell);
	free(partial_exp);
	if (word[*i])
	{
		tmp = expand_variable(word, i, shell, exp_w);
		exp_w = tmp;
	}
	return (exp_w);
}

char	*expander(char *input, t_shell *shell)
{
	char	*expanded_word;
	char	*tmp2;
	int		i;
	int		opened;
	// char	*result;

	opened = 0;
	i = 0;
	expanded_word = NULL;
	if (check_quote_closed(input) == FALSE)
		exit_and_free(shell, "Error : quote not closed");
	if (input != NULL && ft_strchr(input, '$'))
	{
		while (input[i])
		{
			
			if (input[i] == '$' && input[i + 1] != '\0' )
			{
				expanded_word = no_guillemets(input, &i, shell);
				// result = ft_st
				printf("expanded_word: %s\n", expanded_word);
				
				// i =+ ft_
			}				
			else
				is_quoted(input, &i, &opened);
			printf("i: %d\n", i);
			i++;
		}
	}
	else if (init_exp_checks(input, 0))
	{
		tmp2 = symbols(input);
		(free(input), input = tmp2);
	}
	return (input);
}
