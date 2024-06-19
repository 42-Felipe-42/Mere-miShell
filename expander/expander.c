/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/19 13:01:36 by louismdv         ###   ########.fr       */
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

//obj: parcourir entrée jusqu'à: '_' ou char non alphanum, stocker dans 'dest' et comp avec env
//entrée: input sur indice $
//sortie: valeur associée a env
char	*expand(char *input, int i, t_env *envp)
{
	char	*dest;
	char	*env;
	int		j;

	printf("*i : [%d]\n", i);
	dest = (char *)malloc(strlen(input) + 1);
	env = NULL;
	if (input[i] == '$' && input[i + 1] == '\0' /*&& !ft_isalnum(input[i + 1])*/) // "$"
		return (input);
	printf("*i : [%d]\n", i);
	if (input[i] == '$')
		i += 1;
	j = 0;
	printf("*i : [%d]\n", i);
	printf("input[i]: [%c]\n", input[i]);
	while (input[i] && (ft_isalpha(input[i]) || input[i] == '_')) // $$A
	{
		printf(RED"OK\n"RESET);
		// if (input[i] == '$' && !ft_isalnum(input[i + 1]))
		// {
		// 	printf(RED"input: [%s]\n"RESET, input);
		// 	return (input);
		// }
		dest[j++] = input[i];
		i += 1;
	}
	dest[j] = '\0';
	printf(RED"dest: [%s]\n"RESET, dest);
	printf("*i : %d\n", i);
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
				return (expand(word, i, envp));
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
	if (word[i] && 
		(ft_strchr(word + i, '$') != NULL
		|| ft_strnstr(word + i, " $", ft_strlen(word + i)) != NULL
		|| ft_strnstr(word + i, "'$", ft_strlen(word + i)) != NULL
		|| word[2] == '$' || word[1] == '$' || word[0] == '$'))
		return (TRUE);
	else
		return (FALSE);
}

char	*find_pwd(char *str, int *i, t_shell *shell)
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
	char	*exp_w = NULL;
	char	*post;
	char	*tmp;
	
	(void)shell;
	(void)tmp;
	while (lex)
	{
		i = 0;
		while (lex->word[i] && which_quote(lex->word[0]) != S_QUOTE && check_conditions(lex->word, i))
		{
			if (lex->word[0] == '$' && !ft_isdigit(lex->word[1])) 	// $HOME - sans guillmets
			{
				while (lex->word[i] && ft_strchr(lex->word + i, '$'))
				{
					i++;
					tmp = expand(lex->word, i, envp);
					i = ft_strchr(lex->word + i, '$') - lex->word;
					if (!tmp)
					{
						lex->word = exp_w;
						free(exp_w);
						break;
					}
					else if (!exp_w)
						new_w = tmp;
					else
						new_w = ft_strjoin(exp_w, tmp);
					exp_w = new_w;
					if (i < 0)
						break;
				}
				lex->word = exp_w;
				break ;
			}
			post = find_post(lex->word, &i);
			if (ft_isdigit(lex->word[i + 1])) 						// $1
			{
				new_w = ft_strndup(lex->word, i);
				if (lex->word[i + 1] == '0')
					new_w = ft_strjoin(new_w, shell->av);
				i += 2;
				post = ft_strdup(lex->word + i);
				new_w = ft_join_free(new_w, post);
				printf("new_w : [%s]\n", new_w);
				free(post);
				i = -1;
			}
			else
				new_w = ft_strndup(lex->word, i);
			if (ft_strchr(lex->word + i, '$') == NULL)
			{
				printf("lex->word[i] : [%c]\n", lex->word[i]);
				lex->word = new_w;
				printf("lex->word: [%s]\n", lex->word);
			}
			if (lex->word[i] == '$' && ft_isalpha(lex->word[i + 1]) && i >= 0) // expand lex->word[i] et on ajoute entre new_w et post
			{
				printf("new_w = [%s]\n", new_w);
				printf("exp_pars: [%s]\n", exp_pars(lex->word + i, envp));
				printf("post = [%s]\n", post);
				exp_w = ft_join_free(new_w, exp_pars(lex->word + i, envp));
				i = ft_strlen(exp_w);
				new_w = ft_join_free(exp_w, post);
				free(lex->word);
				lex->word = new_w;
				printf(GREEN"lex->word : [%s]\n"RESET, lex->word);
				printf(GREEN"lex->word + i : [%s]\n"RESET, lex->word + i);
				printf("i : %d\n", i);
			}
			else if(ft_strchr(lex->word + i, '$') == NULL && i >= 0)
				break ;
			else
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

	post = NULL;
	printf("pre word: [%s]\n", word);
	printf("*i : %d\n", *i);
	
	// while (word[*i] == '$' && (word[*i + 1] == '$' || word[*i + 1] == ' '))
	// {
	// 	*i += 2;
	// 	*i = ft_strchr(word + *i, '$') - word;
	// 	printf(RED"*i : %d\n"RESET, *i);
	// }
	printf(RED "ft_strchr: [%s]\n" RESET, ft_strchr(word + *i, '$'));
	
	*i = ft_strchr(word + *i, '$') - word;
	if (word[*i] == '$' && ft_isdigit(word[*i + 1])) // dolls + num
	{
		printf("word[i] : %c\n", word[*i]);
		post = ft_strdup(word + *i + 2);
	}
	else
	{
		delimiter = ft_strchr(word + *i + 1, ' ') - word;
		if (delimiter < 0)
			delimiter = ft_strchr(word + *i + 1, '$') - word;
		if (delimiter < 0)
			delimiter = ft_strchr(word + *i + 1, '\'') - word;
		if (delimiter < 0)
			delimiter = ft_strchr(word + *i + 1, '\"') - word;
		if (delimiter < 0)
			delimiter = ft_strchr(word + *i + 1, '\0') - word;
		post = ft_strdup(word + delimiter);
	}
	printf("post *i : [%d]\n", *i);
	printf("find_post return : [%s]\n\n", post);
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
