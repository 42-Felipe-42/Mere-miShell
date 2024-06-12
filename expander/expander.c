/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/12 18:19:15 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// chercher dest dans env, si trouve expand, sinon NULL
char	*find_env(char *dest, t_env *envp)
{
	while (envp)
	{
		if (ft_strcmp(envp->value, dest) == 0)
		{
			if (envp->value[ft_strlen(dest)] == '=')
				return (envp->value);
		}
		envp = envp->next;
	}
	return (NULL);
}

// return valeur associee a variable ENV
char	*expand(char *input, int i, t_env *envp)
{
	char	*dest;
	char	*env;
	int		j;

	dest = (char *)malloc(strlen(input) + 1);
	env = NULL;
	i++;
	j = 0;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
	{
		// printf("%s\n",dest);
		dest[j++] = input[i++];
	}
	dest[j] = '\0';
	env = find_env(dest, envp);
	if (!env)
		env = "", free(dest);
	return (env);
}

// decider si oui ou non on expand une valeur
char	*expand_parsing(char *word, t_env *envp)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[0] == '$') // word = $...
			return (expand(word, i, envp));
		else if (which_quote(word[i]) == D_QUOTE)
		{
			if (word[1] == '$') // word = "$...."
				return (expand(word, 1, envp));
			else // word = "....$..._$..."
			{
				if (ft_strnstr(word, " $", ft_strlen(word)) != NULL)
				{
					i = ft_strnstr(word, " $", ft_strlen(word)) - word;
					return (expand(word, i + 1, envp));
				}
				// else
				// 	break ;
			}
		}
		i++;
	}
	return (word);
}

t_lexer	*expander(t_lexer *lex, t_env *envp)
{
	int		i;
	char	*expanded;
	char	*new_word;
	char *expand_word;
	while (lex)
	{
		i = 0;
		new_word = NULL;
		while (lex->word[i])
		{
			expand_word = strcpy(new_word,lex->word[i]);
			if (lex->word[i] == '$' && which_quote(lex->word[0]) != S_QUOTE)
			{
				expanded = expand_parsing(lex->word + i, envp);
				if (expanded)
				{

					expand_word = ft_strjoinandfree(expand_word, lex->word[i]);
					
				}
			}
			i++;
		}
		lex = lex->next;
	}
	return (lex);
}
// copier la variable d'env dans un liste chainee
t_env	*store_env(char **env)
{
	t_env	*store_value;
	char	*str;
	int		i;

	str = NULL;
	store_value = NULL;
	i = 0;
	if (!env)
		return (0);
	while (env[i])
	{
		str = ft_strdup(env[i]);
		if (!str)
			return (0);
		add_node(&store_value, str);
		i++;
	}
	return (store_value);
}

void	print_list(t_env *env)
{
	while (env)
	{
		printf("%s \n", env->value);
		env = env->next;
	}
}
