/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:25:42 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/02 11:21:14 by plangloi         ###   ########.fr       */
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

void	skip_and_copy(char *input, int *i, char **dest, t_shell *shell)
{
	int		opened;
	int		start;
	char	*tmp;

	tmp = NULL;
	opened = which_quote(input[*i]);
	start = *i;
	if (!opened)
	{
		tmp = copy_if_not_quoted(input, i, start, tmp);
		*dest = ft_join_free(*dest, tmp);
		if (!dest)
			(free(tmp), exit_and_free(shell, "ERROR : skip_and_copy"));
		return (free(tmp));
	}
	(*i)++;
	tmp = copy_if_quoted(input, i, opened, start);
	*dest = ft_join_free(*dest, tmp);
	if (!dest)
		(free(tmp), exit_and_free(shell, "ERROR : skip_and_copy"));
	free(tmp);
}

void	has_dols(char *input, int *i, t_shell *shell, char **result)
{
	char	*exp_w;

	exp_w = NULL;
	while (input[*i])
	{
		if (input[*i] == '$' && input[*i + 1] != '\0')
		{
			exp_w = no_guillemets(input, i, shell);
			*result = join_and_free(*result, exp_w, shell);
			free(exp_w);
			(*i)++;
			while (input[*i] != '\0' && input[*i] != ' ' && input[*i] != '\''
				&& input[*i] != '\"' && input[*i] != '$'
				&& !init_exp_checks(input, *i))
				(*i)++;
		}
		else
			skip_and_copy(input, i, result, shell);
	}
}

char	*expander(char *input, t_shell *shell)
{
	int		i;
	char	*result;

	result = ft_strdup("");
	i = 0;
	if (input != NULL && ft_strchr(input, '$'))
		has_dols(input, &i, shell, &result);
	else
		return (free(result), input);
	return (result);
}
