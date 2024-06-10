/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/06/10 16:49:13 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// return valeur associee a variable ENV
char	*expand(char *input, int i, t_env *env)
{
	char	*dest;
	char	*env;
	int		j;

	dest = (char *)malloc(strlen(input) + 1);
	env = NULL;
	i++;
	j = 0;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		dest[j++] = input[i++];
		&str[i]
	dest[j] = '\0';
	
	if (!env)
		env = "", free(dest);
	return (env);
}

int	between_quotes(char *input)
{
	int	i;
	int	quote_type;

	i = 0;
	while (quote_de_porc(input[i]) == 0 && input[i] != '$')
	{
		i++;
	}
	quote_type = quote_de_porc(input[i]);
	if (quote_type == D_QUOTE)
	{
		while (input[i] && quote_de_porc(input[i]) != quote_type)
		{
		}
	}
}

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
		if(!str)
			return (0);
		add_node(&store_value, str);
		i++;
	}
	return (store_value);
}

void print_list(t_env *env)
{
	while (env)
	{
		printf("%s \n", env->value);
		env = env->next;
	}
}

// int	main(int ac, char **av, char **envp)
// {
// 	(void) ac;
// 	(void) av;
// 	int	i;

// 	i = 1;
// 	t_env *env;
// 	env = store_env(envp);
// 	print_list(env);
// 	while (av[i])
// 	{
// 		printf("%s ", find_dollars(av[i], env));
// 		i++;
// 	}
// 	printf("\n");
// 	return (0);
// }

// cherche dollar dans input a partir de i, et expand $
// char	*find_dollars(char *input)
// {
// 	int		i;
// 	bool	quote;

// 	i = 0;
// 	quote = false;
// 	while (input[i])
// 	{
// 		if (input[i] == '$' && quote == false)
// 			input = expand(input, i);
// 		i++;
// 	}
// 	return (input);
// }