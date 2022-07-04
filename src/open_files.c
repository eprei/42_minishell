/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:50:10 by olmartin          #+#    #+#             */
/*   Updated: 2022/07/04 14:45:32 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*here_input(char *limiter, int fd)
{
	char	*str;
	char	*n_lim;
	size_t	l_lim;

	n_lim = ft_strjoin(limiter, "\n");
	l_lim = ft_strlen(n_lim);
	str = (char *)malloc(sizeof(char) * 90);
	str = "";
	while (str)
	{
		ft_printf(">");
		str = get_next_line(0);
		if (ft_strncmp(str, n_lim, l_lim) == 0 && (l_lim == ft_strlen(str)))
			break ;
		write(fd, str, ft_strlen(str));
	}
	free(str);
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
		in_file = here_input(limiter, cmd->infile);
		close(fd);
	}
	//else
	cmd->infile = open(in_file, O_RDONLY);
	//printf("Unlink state %d\n", unlink("tmp_here"));
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
