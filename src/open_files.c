/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:50:10 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/20 14:40:28 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*here_input(char *limiter)
{
	char	*str;
	char	*n_lim;
	int		fd;
	size_t	l_lim;

	n_lim = ft_strjoin(limiter, "\n");
	l_lim = ft_strlen(n_lim);
	str = (char *)malloc(sizeof(char) * 90);
	str = "";
	fd = open("tmp_here", O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd < 0)
	{
		printf("Error open file out\n");
		return (NULL);
	}
	while (str)
	{
		str = get_next_line(0);
		if (ft_strncmp(str, n_lim, l_lim) == 0 && (l_lim == ft_strlen(str)))
			break ;
		write(fd, str, ft_strlen(str));
	}
	close(fd);
	free(str);
	return ("tmp_here");
}

int	open_in_files(char *in_file, char *limiter, t_cmd *cmd)
{
	if (limiter != NULL)
	   in_file = here_input(limiter);
	cmd->infile = open(in_file, O_RDONLY);
	if (cmd->infile < 0)
		return (1);
	else
		return (0);
}
	
int	open_outfiles(char *out_file, int append, t_cmd *cmd)
{
	if (append == 0)
		cmd->outfile = open(out_file, O_TRUNC | O_CREAT | O_RDWR, 0644);
	else
		cmd->outfile = open(out_file, O_APPEND | O_CREAT | O_RDWR, 0644);
	if (cmd->outfile < 0)
		return (1);
	else
		return (0);
}

