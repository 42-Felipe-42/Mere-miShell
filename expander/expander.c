/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/31 13:30:14 by felipe           ###   ########.fr       */
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

	dst = ft_calloc(strlen(input) + 1, sizeof(char *));
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

char	*find_excode(char *str, t_shell *shell)
{
	if (!ft_strncmp(str, "$?", 2) || !ft_strncmp(str, "$?$", 3))
		str = ft_itoa(shell->tmpexit_code);
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
		exp_w = join_and_free(exp_w, partial_exp, shell);
		free(partial_exp);
		if (word[i])
		{
			tmp = expand_variable(word, &i, shell, exp_w);
			exp_w = tmp;
		}
		if (ft_strchr(word + i, '$') == NULL)
			break ;
		i++;
	}
	return (exp_w);
}
