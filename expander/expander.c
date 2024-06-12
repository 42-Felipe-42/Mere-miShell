/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/12 11:31:02 by plangloi         ###   ########.fr       */
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
		while (lex->word[i] && !flag && which_quote(lex->word[0]) != S_QUOTE)
		{
			if (lex->word[i] == '$' && !which_quote(lex->word[i]))
				flag = TRUE;
			else if (which_quote((lex->word[i]) == D_QUOTE))
			{
				i = ft_strchr(lex->word, ' ') - (lex->word);
				if (!i && ft_strchr(&lex->word[i + 1], '$'))
					flag = TRUE;
			}
			else if (lex->word[0] == '$'
				&& which_quote((lex->word[i]) == D_QUOTE))
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
