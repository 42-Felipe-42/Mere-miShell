/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:24:56 by louismdv          #+#    #+#             */
/*   Updated: 2024/08/19 10:09:31 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*join_and_free(char *exp_w, const char *suffix, t_shell *shell)
{
	char	*new_exp_w;

	new_exp_w = NULL;
	new_exp_w = ft_strjoin(exp_w, suffix);
	if (!new_exp_w)
	{
		free(exp_w);
		exit_and_free(shell, "Error : ft_strjoin expander");
	}
	free(exp_w);
	return (new_exp_w);
}

int	handle_dols(char *word, int *i, t_shell *shell, char **exp_w)
{
	int	dols;

	dols = 0;
	while (word[*i] && word[*i] == '$')
	{
		dols++;
		if ((word[*i] == '$' && word[*i + 1] == '$') || (word[*i] == '$'
				&& word[*i + 1] == '\0' && dols != 1))
			*exp_w = join_and_free(*exp_w, "$", shell);
		else
			break ;
		(*i)++;
	}
	return (dols);
}

char	*expand_join(char *word, int *i, char *exp_w, t_shell *shell)
{
	char	*tmp;
	int		dols;

	dols = count_dols(word, *i);
	shell->flag = 0;
	if (dols % 2 != 0)
	{
		tmp = expand(word, *i, shell);
		if (tmp[0] == '\0')
			shell->flag = 1;
	}
	else
	{
		tmp = ft_strndup_dol(word + *i);
		shell->flag = 1;
		if (!tmp)
		{
			free(exp_w);
			exit_and_free(shell, "Error :  ft_strjoin expander");
		}
	}
	exp_w = join_and_free(exp_w, tmp, shell);
	if (tmp && shell->flag == 1)
		free(tmp);
	return (exp_w);
}

char	*expand_variable(char *word, int *i, t_shell *shell, char *exp_w)
{
	char	*tmp;
	char	*expansion_result;
	char	*tmp2;

	handle_dols(word, i, shell, &exp_w);
	if (!ft_strncmp(word + *i, "$0", 2) || !ft_strncmp(word + *i, "$0$", 3))
		exp_w = join_and_free(exp_w, find_pwd(word + *i, shell), shell);
	else if (!ft_strncmp(word + *i, "$?", 2) || !ft_strncmp(word + *i, "$?$",
			3))
	{
		tmp = find_excode(word + *i, shell);
		expansion_result = join_and_free(exp_w, tmp, shell);
		free(tmp);
		exp_w = expansion_result;
	}
	else if (word[*i] && word[*i] == '$' && word[*i + 1] != '$')
		exp_w = expand_join(word, i, exp_w, shell);
	if (word[*i] && init_exp_checks(word, *i))
	{
		tmp2 = ft_strndup(&word[*i], 1);
		exp_w = join_and_free(exp_w, tmp2, shell);
		free(tmp2);
	}
	return (exp_w);
}

int	init_exp_checks(char *word, int i)
{
	if (word && (word[i] == ' ' || word[i] == '-' || word[i] == '='
			|| word[i] == '+' || word[i] == ']' || word[i] == '['
			|| word[i] == '\'' || word[i] == '/' || word[i] == '}'
			|| word[i] == '{' || word[i] == '%' || word[i] == '&'))
		return (1);
	return (0);
}
