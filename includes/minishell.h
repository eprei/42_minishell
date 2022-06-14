/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:01:49 by Emiliano          #+#    #+#             */
/*   Updated: 2022/06/14 16:02:46 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <readline/readline.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <stddef.h>
# include <readline/history.h>
# include <termios.h>

# define FALSE 0
# define TRUE 1

# define CLOSED 0
# define OPEN 1

# define NO_INIT 0

/* ***************************** STRUCTURES ********************************* */

int g_exit_status;

typedef struct s_count_words
{
    int quote_type;
    int quote_status;
    int counter;
} t_count_words;

typedef struct s_fill_array
{
	int		s_len;
    int     quote_simple;
    int     quote_double;
    int     i;
    int     start_index;
    int     tab_index;    
}           t_fill_array;

typedef struct s_cmd
{
	char            **full_cmd;
	char            *full_path;
	int             infile;
	int	            outfile;
    struct s_cmd    *next;
    struct s_cmd    *prev;
}			        t_cmd;

typedef struct s_prompt
{
	t_cmd  *cmds;
	char	**envp;
	pid_t	pid;
    char    *prompt_text;
}			t_prompt;

typedef struct s_var
{
    char    *line;
    char    **split;
    char    **subsplit;
}           t_var;

/* *****************************  main.c  ********************************* */

char    *get_prompt(char **envp);

/* *************************** node_management ***************************** */

// void	start_stack(t_node **tail, t_node **head, int value);
// void	insert_beginning_stack(t_node **tail, int value);
// void	add_command_to_list(t_node **head, int value);

void    ft_new_prompt(int sig);
void    sig_quit(int sig);

/* *****************************  split.c  ********************************* */

void    init_count_words_struct(t_count_words *w);
int    ft_count_words(const char *str, char *caracter);
char	**ft_split_str_with_spaces_and_quotes(char const *s);
void    ft_fill_array(char **splited, char const *str, char *caracter);

/* ****************************  subsplit.c  ******************************* */

void    fn_sub_split(t_var *v);
char	**ft_cmdsubsplit(char const *s, char *set);

/* *****************************  exit.c  *********************************** */
void    ft_exit(int exit_status);

/* *****************************  BRANCHE o_pipe  *************************** */

/* *****************************  var_utils.c  *************************** */

int		env_var_exist(char *name, char **envp);
char	*get_env(char *name, char **my_envp);
int		set_env(char *name, char * var, char **my_env);

/* *****************************  var_env.c  *************************** */

int		export_builtin(t_cmd *cmd, char **envp);
int		unset_builtin(char *name, char **my_envp);
void	env_builtin(t_prompt *s_pr);

/* *****************************  utils_tab.c  *************************** */

int		tablen(char **t);
char	**tab_add(char **src, char *add);
void	tab_free(char **tab);
void	print_tab(char **tab);
char	**tab_delone(char **src, char **dest, int to_del);

char	*here_input(char *limiter);
int		mini_pwd(char **my_envp);
void	fd_putendl_fd(char *s, int fd);
char	**init_envp(char **envp);
void	ft_print_tab_model(char **temp);
int		mini_cd(t_cmd *cmd, char **my_env);
#endif
