/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:31:32 by olmartin          #+#    #+#             */
/*   Updated: 2022/07/18 11:31:42 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*here_input(char *limiter, int fd)
{
	char	*str;
	size_t	l_lim;

	l_lim = ft_strlen(limiter);
	str = "";
	while (str)
	{
		ft_printf(">");
		str = get_next_line(0);
		if (!str)
		{
			ft_putstr_fd(limiter, 2);
			ft_putstr_fd(" should be used as LIMITER\n", 2);
			break ;
		}
		else if (ft_strncmp(str, limiter, l_lim) == 0 && \
			(l_lim == ft_strlen(str)))
			break ;
		write(fd, str, ft_strlen(str));
		free(str);
	}
	free(str);
	free (limiter);
	return ("tmp_here");
}

int	open_in_files(char *in_file, char *limiter, t_cmd *cmd)
{
	int	fd;

	if (cmd->infile != 0)
		close(cmd->infile);
	if (limiter != NULL)
	{
		fd = open("tmp_here", O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (fd < 0)
			return (FALSE);
		in_file = here_input(ft_strjoin(limiter, "\n"), fd);
		close(fd);
	}
	cmd->infile = open(in_file, O_RDONLY);
	if (limiter != NULL)
		unlink("tmp_here");
	if (cmd->infile < 0)
		return (FALSE);
	else
		return (TRUE);
}

int	open_outfiles(char *out_file, int append, t_cmd *cmd)
{
	if (cmd->outfile != 1)
		close(cmd->outfile);
	if (append == FALSE)
		cmd->outfile = open(out_file, O_TRUNC | O_CREAT | O_RDWR, 0644);
	else
		cmd->outfile = open(out_file, O_APPEND | O_CREAT | O_RDWR, 0644);
	if (cmd->outfile < 0)
		return (FALSE);
	else
		return (TRUE);
}
