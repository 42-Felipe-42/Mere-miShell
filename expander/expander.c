/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/08/20 15:58:39 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// chercher dest dans env, si trouve expand, sinon ""
char	*expand(char *input, int i, t_shell *shell)
{
	char	*dst;
	char	*env;
	int		j;

	dst = ft_calloc(ft_strlen(input) + 1, sizeof(char *));
	if (!dst)
		exit_and_free(shell, "Error : Malloc expander");
	env = NULL;
	if (input[i] == '$')
		i++;
	j = 0;
	// printf("input: %s\n", input + i);
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_')
		&& input[i] != '\'' && input[i] != '\"')
	{
		dst[j++] = input[i];
		i++;
	}
	dst[j] = '\0';
	env = find_env(dst, shell->env);
	if (!env)
		env = ft_strdup("");
	return (free(dst), env);
}

char	*find_pwd(char *str, t_shell *shell)
{
	if (!ft_strncmp(str, "$0", 2) || !ft_strncmp(str, "$0$", 3))
		str = shell->av;
	else
		return (NULL);
	return (str);
}

// expand first part of the input. ex: $HOME$$HOME s'arrete au 2eme $
char	*initialize_expansion(char *word, int *i)
{
	char	*exp_w;

	if (*i == 0 && word[*i] != '\0' && (ft_isalnum(word[*i])
			|| init_exp_checks(word, *i)))
	{
		exp_w = ft_strndup_dol(word);
		while (word[*i] != '$' && word[*i])
			(*i)++;
		// printf("exp_w: %s\n", exp_w);
		return (exp_w);
	}
	else
		exp_w = ft_strdup("");
	return (exp_w);
}

// returns expanded word
char	*no_guillemets(char *word, int *i, t_shell *shell)
{
	char	*exp_w;
	char	*tmp;

	// char	*partial_exp;
	exp_w = ft_strdup("");
	// partial_exp = initialize_expansion(word, i);
	// exp_w = join_and_free(exp_w, partial_exp, shell);
	// free(partial_exp);
	if (word[*i])
	{
		tmp = expand_variable(word, i, shell, exp_w);
		exp_w = tmp;
	}
	// printf("i : %d\n", *i);
	return (exp_w);
}

void	skip_and_copy(char *input, int *i, char *dest)
{
	int		opened;
	int		dest_index;
	int		start;
	char	*tmp;

	dest_index = ft_strlen(dest);
	opened = which_quote(input[*i]);
	// printf("skiping... input[i] from: [%c]\n", input[*i]);
	if (!opened)
	{
		start = *i;
		while (input[*i] != '$' && input[*i] != '\'' && input[*i] != '\"'
			&& input[*i] != '\0')
			(*i)++;
		tmp = ft_strndup(input + start, *i);
		dest = ft_join_free(tmp, dest);
		return ;
	}
	(*i)++;
	while (opened && input[*i])
	{
		if (opened == which_quote(input[*i]))
			opened = 0;
		else
			dest[dest_index++] = input[*i];
		(*i)++;
	}
	dest[dest_index] = '\0';
}

char	*expander(char *input, t_shell *shell)
{
	char	*exp_w;
	int		i;
	char	*result;

	result = ft_strdup("");
	i = 0;
	exp_w = NULL;
	if (check_quote_closed(input) == FALSE)
		exit_and_free(shell, "Error : quote not closed");
	if (input != NULL && ft_strchr(input, '$'))
	{
		while (input[i])
		{
			if (input[i] == '$' && input[i + 1] != '\0')
			{
				exp_w = no_guillemets(input, &i, shell);
				result = join_and_free(result, exp_w, shell);
				free(exp_w);
				// printf("input[i]: [%c]\n", input[i]);
				i++;
				while (input[i] != '\0' && input[i] != ' ' && input[i] != '\''
					&& input[i] != '\"' && input[i] != '$')
					i++;
				// printf("result expand: [%s]\n", result);
			}
			else
			{
				skip_and_copy(input, &i, result);
				// printf("result skip_copy: [%s]\n", result);
			}
			// printf("i: %d\n", i);
		}
	}
	else if (init_exp_checks(input, 0))
	{
		exp_w = symbols(input);
		(free(input), result = exp_w, free(exp_w));
	}
	else
	{
		free(result);
		return (input);
	}
	// printf("result: %s\n", result);
	return (result);
}
