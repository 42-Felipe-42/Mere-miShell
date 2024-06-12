/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/12 11:00:22 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//chercher dest dans env, si trouve expand, sinon NULL
char *find_env(char *dest, t_env *envp)
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

//return valeur associee a variable ENV
char	*expand(char *input, int i, t_env *envp)
{
	char	*dest;
	char	*env;
	int		j;

	printf("src : %s\n\n", input);
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
	printf("dest :%s \n\n", dest);
	env = find_env(dest, envp);
	printf("env : %s \n\n", env);
	if (!env)
		env = "", free(dest);
	return (env);
}

//decider si oui ou non on expand une valeur
char	*expand_parsing(t_lexer *lex, t_env *envp)
{
	int		i;
	bool	flag;
	char	*result;

	result = NULL;
	while (lex)
	{
		i = 0;
		flag = FALSE;
		while (lex->word[i] && !flag)
		{
			if (lex->word[i] == '$' && !quote_de_porc((lex->word[i]))) //$HOME
				flag = TRUE;
			else if (quote_de_porc((lex->word[i]) == D_QUOTE)) //"jwfjpewijfp $HOME ewce"
			{
				i = ft_strchr(lex->word, ' ') - (lex->word);
				if (ft_strchr(&lex->word[i + 1], '$'))
					flag = TRUE;
			}
			else if (lex->word[i+1] == '$' && quote_de_porc((lex->word[i]) == D_QUOTE)) //"$HOME"
				flag = TRUE;
			if (flag)
				result = expand(lex->word, i, envp);
			i++;
		}
		lex = lex->next;
	}
	return (result);
}

//copier la variable d'env dans un liste chainee
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


// char *expand_parsing(t_lexer *lex, t_env *envp) {
//     char *result = NULL;
//     char *expanded_value;
//     int i;

//     while (lex) {
//         i = 0;
//         while (lex->word[i]) {
//             if (lex->word[i] == '$') {
//                 expanded_value = expand(lex->word, i, envp);
//                 if (expanded_value)
// 				{
// 					result = ft_strdup(expanded_value);
//                 }
//             }
// 					i++;
//         }
//         lex = lex->next;
//     }
//     return (result);
// }
// cherche dollar dans input a partir de i, et expand $


// int	ft_strictncmp(const char *s1, const char *s2, int n)
// {
// 	int	i;

// 	i = 0;
// 	while ((s1[i] || s2[i]) && i < n)
// 	{
// 		if (s1[i] != s2[i])
// 			return (-1);
// 		i++;
// 	}
// 	if (i < n || s1[i])
// 		return (-1);
// 	return (0);
// }