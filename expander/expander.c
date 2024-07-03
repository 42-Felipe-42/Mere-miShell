/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/03 15:36:42 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// chercher dest dans env, si trouve expand, sinon NULL
char	*find_env(char *dest, t_env *envp)
{
	int		dest_len;
	char	*equal_sign;

	dest_len = strlen(dest);
	while (envp)
	{
		// Find the '=' in the current environment variable string
		equal_sign = strchr(envp->value, '=');
		// Check if '=' is found and the part before it matches 'dest'
		if (equal_sign && (equal_sign - envp->value == dest_len)
			&& strncmp(envp->value, dest, dest_len) == 0)
			return (equal_sign + 1); // Return the value part after '='
		envp = envp->next;
	}
	return (NULL);
}

// obj: parcourir entrée jusqu'à: '_' ou char non alphanum,
// stocker dans 'dest' et comp avec env
// entrée: input sur indice $
// sortie: valeur associée a env
char	*expand(char *input, int i, t_env *envp)
{
	char	*dest;
	char	*env;
	int		j;

	dest = (char *)malloc(strlen(input) + 1);
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
	return (env);
}

char	*find_pwd(char *str, t_shell *shell)
{
	if (ft_strncmp(str, "$0", 2) == 0 || ft_strncmp(str, "$0$", 3) == 0 )
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

char	*no_guillemets(char *word, t_shell *shell)
{
	char	*tmp;
	char	*exp_w;
	int		dols;
	int		i;

	tmp = "";
	exp_w = "";
	i = 0;
	while (word[i])
	{
		if (i == 0 && ft_isalnum(word[i]))
		{
			exp_w = ft_strndup_dol(word);
			while (word[i] != '$')
				i++;
		}
		dols = 0;
		while (word[i] && word[i] == '$')
		{
			dols++;
			if (word[i] && word[i] == '$' && word[i + 1] == '$')
				exp_w = ft_strjoin(exp_w, "$");
			else
				break ;
			i++;
		}
		if (find_pwd(word +i, shell))
			exp_w = ft_strjoin(exp_w, find_pwd(word +i, shell));
		if (word[i] && word[i] == '$' && word[i + 1] != '$')
		{
			if (dols % 2 != 0)
				tmp = expand(word, i, shell->env);
			else
				tmp = ft_strndup_dol(word + i);
			exp_w = ft_strjoin(exp_w, tmp);
		}
		i = ft_strchr(word + i + 1, '$') - word;
		if (i < 0)
			break ;
	}
	word = exp_w;
	return (word);
}
