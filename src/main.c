/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:01:33 by Emiliano          #+#    #+#             */
/*   Updated: 2022/06/13 15:20:47 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *get_prompt(char **envp)
{
    char    *str_get_info;
    char    *str_prompt;

    str_get_info = get_env("USER", envp);
    str_prompt = ft_strjoin(str_get_info, "@minishell42$ ");
    // free(str_get_info);
    return (str_prompt);
}

void    init_t_var_main(t_var *v)
{
    v->line = NULL;
    v->split = NULL;
    // v->subsplit = NULL;
    v->subsplit = malloc(sizeof(char*) * 5);
}

void    init_t_prompt(t_prompt *prompt, char **envp)
{
    prompt->cmds = NULL;
    prompt->envp = init_envp(envp);
    prompt->pid = 0;   
    prompt->prompt_text = get_prompt(prompt->envp); // substitution for Olivier's fn_duplicate_environement 
}

int main(int argc, char **argv, char **envp)
{
    t_var       v;
    t_prompt    prompt;

    exit_status = 0;
    init_t_var_main(&v);
    init_t_prompt(&prompt, envp);
    signal(SIGINT, ft_new_prompt); // ctrl + C
    signal(SIGQUIT, sig_quit); // ctrl + '\'
    // CTRL+D = EOF of standard input, wich ends the proces; LEARN HOW TO HANDLE THIS
    while (argc == 1)
    {
        v.line = readline(prompt.prompt_text); // copy stdin to line
        // fn_add_history(line); // need to be coded or use the real add_history function
        v.split = ft_split_str_with_spaces_and_quotes(v.line); // this function returns NULL when there're inconsistences with quotes
        free(v.line);
         // if $ modifier la variable avec ->>> char	*get_env(char *name, char **my_envp);

        if (v.split == NULL)
        {
            ft_printf("Error token\n");
            free(v.line);   
        }
        // expand = ft_expand_var(split); // expand variables
        // subsplit = ft_subsplit(expand); // another split if its needed for < > |
        // final_str_trim = ft_final_str_strim(subsplit); // delete 
        else 
        {
            int i = 0;
            while (v.split[i])
            {
                printf("\tsplit just spaces[%d] = %s\n\n ", i, v.split[i]);
                free(v.split[i]);
                i++;
            }
            fn_sub_split(&v);
            i = 0;
            while (v.subsplit[i])
            {
                printf("\tsub split <|> [%d] = %s\n\n ", i, v.subsplit[i]);
                free(v.subsplit[i]);
                i++;
            }
            free(v.subsplit);
            free(v.split);
        }
        // free(expand);
        // free(v.subsplit);
        // free(final_str_trim);    
    }
    return (0);
}
