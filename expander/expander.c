/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/13 19:19:57 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// chercher dest dans env, si trouve expand, sinon NULL
char	*find_env(char *dest, t_env *envp)
{
	int	equal_index;

	while (envp)
	{
		if (ft_strcmp(envp->value, dest) == 0)
		{
			if (envp->value[ft_strlen(dest)] == '=')
			{
				equal_index = ft_strchr(envp->value, '=') - (envp->value) + 1;
				return (envp->value + equal_index);
			}
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
	if (input[i] == '$' && !ft_isalnum(input[i + 1]) && ft_strlen(input) == 1)
		return (input);
	i++;
	j = 0;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
	{
		if (input[i] == '$' && !ft_isalnum(input[i + 1]))
			return (input);
		printf("%s\n", dest);
		dest[j++] = input[i++];
	}
	dest[j] = '\0';
	env = find_env(dest, envp);
	if (!env)
		env = "", free(dest);
	return (env);
}

// decider si oui ou non on expand une valeur
char	*exp_pars(char *word, t_env *envp)
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
				else
					break ;
			}
		}
		i++;
	}
	return (word);
}

bool	check_conditions(char *word, int i)
{
	return (ft_strnstr(word + i, " $", ft_strlen(word + i)) != NULL
		|| ft_strnstr(word + i, "'$", ft_strlen(word + i)) != NULL
		|| word[2] == '$' || word[0] == '$');
}

// return lex expanded
void	expander(t_lexer *lex, t_env *envp)
{
	int		i;
	char	*new_w;
	char	*exp_w;
	char	*post;

	while (lex)
	{
		i = 0;
		while (lex->word[i] && which_quote(lex->word[0]) != S_QUOTE)
		{
			if (check_conditions(lex->word, i))
			{
				if (lex->word[0] == '$')
				{
					lex->word = expand(lex->word, i, envp);
					break ;
				}
				post = find_post(lex->word, &i);
				new_w = ft_strndup(lex->word, i + 1);
			}
			else
				break ;
			i++;
			if (lex->word[i] == '$' && ft_isalnum(lex->word[i + 1]))
			{
				exp_w = ft_join_free(new_w, exp_pars(lex->word + i, envp));
				i = ft_strlen(exp_w);
				new_w = ft_join_free(exp_w, post);
			}
			else
				break ;
			free(lex->word);
			lex->word = new_w;
			i++;
		}
		lex = lex->next;
	}
}

// return ce quil y a apres la variable env $
char	*find_post(char *word, int *i)
{
	int		delimiter;
	char	*post;
	int		tmp;

	post = NULL;
	tmp = ft_strnstr(word, " $", ft_strlen(word)) - word;
	if (tmp < 0)
		tmp = ft_strnstr(word, "'$", ft_strlen(word)) - word;
	*i = tmp;
	delimiter = ft_strchr(word + *i + 1, ' ') - word;
	if (delimiter < 0)
		delimiter = ft_strchr(word + *i + 1, '\'') - word;
	if (delimiter < 0)
		delimiter = ft_strchr(word + *i + 1, '\"') - word;
	if (delimiter > 0)
		post = ft_strdup(word + delimiter);
	return (post);
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
