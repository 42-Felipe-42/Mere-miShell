/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanderbis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/18 17:07:16 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// COMMANDES A CORRIGER:
//"$HOME wedew$SHLVL  sewg $PWD '$HOME'"

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
		// printf("%s\n", dest);
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
	if (ft_strnstr(word + i, "$", ft_strlen(word + i)) != NULL
		|| ft_strnstr(word + i, " $", ft_strlen(word + i)) != NULL
		|| ft_strnstr(word + i, "'$", ft_strlen(word + i)) != NULL
		|| word[2] == '$' || word[1] == '$' || word[0] == '$')
		return (TRUE);
	else
		return (FALSE);
}

char *find_pwd(char *str, int *i, t_shell *shell)
{
	if (ft_strcmp(&str[*i], "$0") && ft_strlen(str) == 2)
		str = shell->av;
	return (str);
}
	// post = find_post(lex->word, &i);
				// if (ft_isdigit(lex->word[i + 1]))
				// {
					// new_w = ft_strndup(lex->word, i);
					// printf("first word : [%s]\n", new_w);
					// if (lex->word[i + 1] == '0')
						// tmp2 = ft_strjoin(new_w, shell->av);
					// printf("$0 [%s]\n", tmp2);
					// i += 2;
					// post = ft_strdup(lex->word + i);
					// printf("post = [%s]\n", post);
					// tmp = ft_join_free(tmp2, post);
					// printf("tmp = [%s]\n", tmp);
					// free(post);
					// new_w = tmp2;
				// }
				// else
// return lex expanded
void	expander(t_lexer *lex, t_env *envp, t_shell *shell)
{
	int		i;
	char	*new_w;
	char	*exp_w;
	char	*post;
	char	*tmp;
	(void)shell;
	while (lex)
	{
		i = 0;
		while (lex->word[i] && which_quote(lex->word[0]) != S_QUOTE)
		{
			if (check_conditions(lex->word, i))
			{
				if (lex->word[0] == '$' && !ft_isdigit(lex->word[1]))
				{
					lex->word = expand(lex->word, i, envp);
					break ;
				}
				post = find_post(lex->word, &i);
				if (ft_isdigit(lex->word[i + 1]))
				{
					new_w = ft_strndup(lex->word, i);
					if (lex->word[i +1] == '0')
						new_w = ft_strjoin(new_w, shell->av);
					i += 2;
					post = ft_strdup(lex->word + i);
					tmp = ft_join_free(new_w, post);
					free(post);
					new_w = tmp;
				}
				else
					new_w = ft_strndup(lex->word, i);
			}
			else
				break ;
			if (lex->word[i] != '$')
				i++;
			if (lex->word[i] == '$' && ft_isalpha(lex->word[i + 1]))
			{
				printf("new_w = [%s]\n", new_w);
				printf("exp_pars: [%s]\n", exp_pars(lex->word + i, envp));
				printf("post = [%s]\n", post);
				exp_w = ft_join_free(new_w, exp_pars(lex->word + i, envp));
				i = ft_strlen(exp_w);
				new_w = ft_join_free(exp_w, post);
			}
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
	printf("pre word: [%s]\n", word);
	printf(RED "ft_strchr: [%s]\n" RESET, ft_strchr(word, '$'));
	if (ft_strchr(word, '$') > 0)
	{
		printf(RED "OKOK\n" RESET);
		tmp = ft_strchr(word, '$') - word;
		printf("tmp = %d\n", tmp);
		*i = tmp;
		printf("after incr i = %d\n", *i);
		delimiter = ft_strchr(word + *i + 1, ' ') - word;
		if (delimiter < 0)
			delimiter = ft_strchr(word + *i + 1, '\'') - word;
		if (delimiter < 0)
			delimiter = ft_strchr(word + *i + 1, '\"') - word;
		if (delimiter < 0)
			delimiter = ft_strchr(word + *i + 1, '\0') - word;
		post = ft_strdup(word + delimiter);
	}
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


// si !alphanum print le $ avec sa valeur,
// sauf $? et $0. Si il y a des num derriere skip le $ et le 1er num et ecrire le reste exemple ($1HOLA
// -> HOLA)

// void	prout(t_env *env, t_lexer *lex)
// {
// 	int	i;

// 	i = 0;
// 	while (lex)
// 	{
// 		i = 0;
// 		while (lex->word[i])
// 		{
// 			if (lex->word[i] == '$' && ft_isdigit(lex->word[i + 1]))
// 				i + 2;
// 			else if (lex->word[i] == '$' && !ft_isalnum(lex->word[i + 1]))
// 			{
// 				while (lex->word[i] != ' ')
// 					i++;
// 			}

// 		}
// 	}
// }
