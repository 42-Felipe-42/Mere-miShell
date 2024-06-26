/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:43:22 by lmerveil          #+#    #+#             */
/*   Updated: 2024/06/26 16:02:08 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void    print_list(t_shell *shell)
{
    t_lexer    *current_lex;

    current_lex = shell->lex;
    while (current_lex)
    {
        if (current_lex->next == NULL)
        {
            ft_putstr_fd(GREEN "Last Node : ", STDOUT_FILENO);
        }
        else
        {
            ft_putstr_fd(RED "Past Node : ", STDOUT_FILENO);
        }
        ft_putstr_fd(current_lex->word, STDOUT_FILENO);
        printf(RESET "\n");
        current_lex = current_lex->next;
    }
}

// void    print_list_cmds(t_shell *shell)
// {
//     t_cmds    *current_cmd;
//     int        i;

//     current_cmd = shell->cmds;
//     while (current_cmd)
//     {
//         i = 0;
//         while (current_cmd->tab && current_cmd->tab[i])
//         {
//             if (current_cmd->next == NULL)
//             {
//                 ft_putstr_fd(GREEN "Last Node : ", STDOUT_FILENO);
//             }
//             else
//             {
//                 ft_putstr_fd(RED "Past Node : ", STDOUT_FILENO);
//             }
//             ft_putstr_fd(current_cmd->tab[i], STDOUT_FILENO);
//             printf(RESET "\n");
//             i++;
//         }
//         current_cmd = current_cmd->next;
//     }
// }

int    main(int ac, char **av, char **envp)
{
    t_lexer    *lex;
    t_lexer    *current;
    char    *input;
    t_env    *env;
    t_shell    *shell;
    // t_cmds    *cmds;

    lex = NULL;
    (void)ac;
    (void)current;
    shell = malloc(sizeof(t_shell));
    env = NULL;
    shell->av = ft_strdup(*av);
    input = av[1];
    env = store_env(envp);
    shell->env = env;
    // cmds = NULL;
    // init_cmds(cmds);
    while (1)
    {
        input = ft_readline();
        lex_str(input, &lex);
        expander(lex, env, shell);
        quote(lex);
        // cmds = create_cmds(lex, cmds);
        shell->lex = lex;
        // shell->cmds = cmds;
        current = shell->lex;
        print_list(shell);
        // print_list_cmds(shell);
    }
    return (0);
}