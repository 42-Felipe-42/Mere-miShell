/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/13 17:24:51 by lmerveil         ###   ########.fr       */
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
		if (word[0] == '$')							// word = $...
			return (expand(word, i, envp));
		else if (which_quote(word[i]) == D_QUOTE)
		{
			if (word[1] == '$')						// word = "$...."
				return (expand(word, 1, envp));
			else									// word = "....$..._$..."
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

// return lex expanded
void	expander(t_lexer *lex, t_env *envp)
{
	int		i;
	char	*new_word;
	char	*expand_word;
	char 	*post;

	post = NULL;
	new_word = NULL;
	while (lex)
	{
		i = 0;
		while (lex->word[i] && which_quote(lex->word[0]) != S_QUOTE)
		{
			if 
				(
				(ft_strnstr(lex->word + i, " $", ft_strlen(lex->word + i)) != NULL
				|| ft_strnstr(lex->word + i, "'$", ft_strlen(lex->word + i)) != NULL)
				
				|| lex->word[2] == '$'
				|| lex->word[0] == '$'
				)
			{	
				printf("OK\n");
				
				if (lex->word[0] == '$')
				{
					lex->word = expand(lex->word, i, envp);
					break;
				}
			post = find_post(lex->word, &i);
				new_word = ft_strndup(lex->word, i + 1);
			}
			else
				break;
			i++;
			if (lex->word[i] == '$')
			{				
				expand_word = ft_strjoin(new_word, expand_parsing(lex->word + i, envp));
				i = ft_strlen(expand_word);
				free(new_word);
				new_word = ft_strjoin(expand_word, post);
			}
			free(lex->word);
			lex->word = new_word;
			if (post != NULL)
				free(post);
			i++;
		}
		lex = lex->next;
	}
	return ;
}

// return ce quil y a apres la variable env $
char	*find_post(char *word, int *i)
{
	int delimiter;
	char *post;
	int tmp;

	post = NULL;
	// printf("word: [%s]\n", word);
	tmp = ft_strnstr(word, " $", ft_strlen(word)) - word;				//donne indice du "_$"
	if (tmp < 0)
		tmp = ft_strnstr(word, "'$", ft_strlen(word)) - word;
	*i = tmp;
	
	// printf("tmp = [%d]\n", tmp);
	delimiter = ft_strchr(word + *i + 1, ' ') - word;					//index of first "" after "_$"
	// printf("delimiter = %d\n", delimiter);
	if (delimiter < 0)
		delimiter = ft_strchr(word + *i + 1, '\'') - word;	
	// printf("delimiter = %d\n", delimiter);								//index of first '\"' after "_$"
	if (delimiter < 0)
		delimiter = ft_strchr(word + *i + 1, '\"') - word;
	// printf("delimiter = %d\n", delimiter);								//index of first '\"' after "_$"
	if (delimiter > 0)
		post = ft_strdup(word + delimiter);	
	// printf("post = [%s]\n", post);
	return(post);
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
