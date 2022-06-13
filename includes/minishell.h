/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:01:49 by Emiliano          #+#    #+#             */
/*   Updated: 2022/06/03 15:01:54 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <stddef.h>

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}			t_prompt;

typedef struct  s_mini
{
	char    **full_cmd;
	char    **full_path;
	int     infile;
	int     outfile;
}       t_mini;

int		mini_pwd(char **my_envp);
char	*here_input(char *limiter);
void	fd_putendl_fd(char *s, int fd);
int		tablen(char **t);
char	**tab_add(char **src, char *add);
int		env_var_exist(char *name, char **envp);
int		export_builtin(t_mini *cmd, char **envp);
char	**init_envp(char **envp);
void	ft_print_tab_model(char **temp);
char	*get_env(char *name, char **my_envp);
int		set_env(char *name, char * var, char **my_env);
int		unset_builtin(char *name, char **my_envp);
void	tab_free(char **tab);
int		mini_cd(t_mini *cmd, char **my_env);
#endif
