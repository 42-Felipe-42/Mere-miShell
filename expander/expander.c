/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/07/01 12:09:52 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// COMMANDES A CORRIGER:
//"$HOME wedew$SHLVL  sewg $PWD '$HOME'"

char *ft_strjoin_char(const char *str, char c)
{
    size_t len = strlen(str);
    char *result = (char *)malloc(len + 2); // +1 for the char and +1 for the null terminator
    if (!result) {
        return NULL; // Memory allocation failed
    }
    ft_strlcpy(result, str, len + 2);
    result[len] = c;
    result[len + 1] = '\0';
    return result;
}

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

	dest = (char *)malloc(strlen(input) + 1);
	env = NULL;
	if (input[i] == '$' && input[i + 1] == '\0') // "$"
		return (input);
	if (input[i] == '$' && input[i + 1] == '$')
		i +=3;
	else if (input[i] == '$')
		i++;
	j = 0;
	while (input[i] && (ft_isalpha(input[i]) || input[i] == '_')) // $$A
	{
		dest[j++] = input[i];
		i += 1;
	}
	dest[j] = '\0';
	printf(RED"dest: [%s]\n"RESET, dest);
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

void	expander(t_lexer *lex, t_env *envp, t_shell *shell)
{
	int		i;
	char	*new_w;
	char	*exp_w = "";
	char	*post;
	char	*tmp;
	int		j = 0;

	(void)shell;
	(void)j;
	(void)tmp;
	while (lex)
	{
		i = 0;
		while (lex->word[i] && which_quote(lex->word[0]) != S_QUOTE && check_conditions(lex->word, i))
		{
			if (lex->word[0] == '$' && lex->word[1] == '\0') 		// $\0 - dollar seul
				break;
			else if (lex->word[0] == '$') 								// $$$$abcd$HOME$$SHLVL-sans guillmets
				return(no_guillemets(&lex->word, i, envp));
			
			post = find_post(lex->word, &i, &new_w);				// "abcd$1abcd$HOME" - avec guillemets
			if (ft_isdigit(lex->word[i + 1]))							// -> $123 - skipper premier chiffre apres $
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
			// else if(ft_strchr(lex->word + i, '$') == NULL && i >= 0)
			// 	break ;
			else
				i++;
		}
		lex = lex->next;
	}
}

// fonction pour expand les cas avec dollar et guillemets: $$$abcd$$$$$HOME$SHLVL
void	no_guillemets(char **word, int i, t_env *envp)
{
	char	*tmp = "";
	char	*exp_w = "";
	int		dols;
	int		counter = 0;

	while ((*word)[i])
	{
		dols = 0;
		printf(RED"i : [%d]\n"RESET, i);
		while ((*word)[i] && (*word)[i] == '$')
		{
			dols++;
			i++;
			exp_w = ft_strjoin(exp_w, "$");
		}
		if (ft_isdigit((*word)[i]))
		{
			i++;
			while ((*word)[i] && (*word)[i] != '$')
			{
				exp_w = ft_strjoin_char(exp_w, (*word)[i]);
				i++;
			}
		}
		else if (dols % 2 != 0)
			tmp = expand(*word, i, envp);
		// else
		// 	tmp = ft_strdup(*word + i);
		printf(RED"tmp: [%s]\n"RESET, tmp);
		if (!tmp)
			exp_w = ft_strjoin(exp_w, tmp);
		// {
		// 	*word = exp_w;
		// 	free(exp_w);
		// 	break;
		// }
		printf(RED"\n	➜ exp_w: [%s]\n\n"RESET, exp_w);
		if (ft_strchr((*word) + i, '$') - *word < 0)
		{
			*word = exp_w;
			printf(BLUE"[no more $ signs: breaking ...]\n"RESET);
			break;
		}
		printf(RED"step exp_w: [%s]\n", exp_w);
		i = ft_strchr((*word) + i, '$') - *word;
		printf(GREEN"counter: %d\n\n"RESET, counter++);
	}
	printf(GREEN"\n	➜ word: [%s]\n\n"RESET, *word);
	*word = exp_w;
}

// return ce quil y a apres la variable env $
char	*find_post(char *word, int *i, char **new_w)		 //"abcd$$$$1abcd$HOME" - avec guillemets
{
	int		delimiter;
	char	*post;
	int		dols;


	dols = 0;
	printf("start *i : [%d], \npre word: [%s]\n", *i, word);
	
    while (word[*i])
    {
		dols = 0;
		while (word[*i] && word[*i] != '$')
			(*i)++;
		while (word[*i] == '$') 
		{
			dols++;
			(*i)++;
		}
		if (dols % 2 != 0)
			break;
	}
	printf("dols : [%d]\n", dols);
	printf("i : [%d]\n", *i);
	
	printf(GREEN"new_w : [%s]\n ft_strchr: [%s]\n"RESET, *new_w, ft_strchr(word + *i, '$'));
	*new_w = ft_strndup(word, *i);
	if (ft_strchr(word + *i, '$') != NULL)
		*i = ft_strchr(word + *i, '$') - word;
	if (word[*i] == '$' && ft_isdigit(word[*i + 1]))
		post = ft_strdup(word + *i + 2);
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
	printf(GREEN"dols : [%d]\n"RESET, dols);
	printf(GREEN"post : [%s]\n"RESET, post);
	return (post);
}


