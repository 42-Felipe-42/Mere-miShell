/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/08/20 16:22:55 by lmerveil         ###   ########.fr       */
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

// returns expanded word
char	*no_guillemets(char *word, int *i, t_shell *shell)
{
	char	*exp_w;
	char	*tmp;

	exp_w = ft_strdup("");
	if (word[*i])
	{
		tmp = expand_variable(word, i, shell, exp_w);
		exp_w = tmp;
	}
	return (exp_w);
}

void	skip_and_copy(char *input, int *i, char **dest)
{
	int		opened;
	int		dest_index;
	int		start;
	char	*tmp;

	dest_index = strlen(*dest);
	opened = which_quote(input[*i]);
	start = *i;
	if (!opened)
	{
		while (input[*i] != '$' && input[*i] != '\'' && input[*i] != '\"'
			&& input[*i] != '\0')
			(*i)++;
		tmp = strndup(input + start, *i - start);
		*dest = ft_join_free(*dest, tmp);
		free(tmp);
		return ;
	}
	(*i)++;
	while (opened && input[*i])
	{
		if (opened == which_quote(input[*i]))
			opened = 0;
		(*i)++;
	}
	tmp = strndup(input + start, *i - start);
	*dest = ft_join_free(*dest, tmp);
	free(tmp);
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
				i++;
				while (input[i] != '\0' && input[i] != ' ' && input[i] != '\''
					&& input[i] != '\"' && input[i] != '$')
					i++;
			}
			else
				skip_and_copy(input, &i, &result);
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
	return (result);
}
