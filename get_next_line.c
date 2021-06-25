/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:45:18 by soahn             #+#    #+#             */
/*   Updated: 2021/06/25 14:00:54 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		chk_newline(char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (src[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	make_line(char **backup, char **line, int end_idx)
{
	char	*tmp;

	(*backup)[end_idx] = '\0';
	*line = ft_strdup(*backup);
	if (*(*backup + end_idx + 1) == '\0')
		tmp = ft_strdup("");
	else
		tmp = ft_strdup((*backup) + end_idx + 1);
	free(*backup);
	*backup = tmp;
}

int		make_line_chk_eof(char **backup, char **line, int size)
{
	int	end_idx;

	if (size < 0)
		return (-1);
	if (!*backup)
	{
		*line = ft_strdup("");
		return (0);
	}
	end_idx = chk_newline(*backup);
	if (end_idx < 0)
	{
		*line = *backup;
		*backup = 0;
		return (0);
	}
	make_line(backup, line, end_idx);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*backup[256];
	char		buf[BUFFER_SIZE + 1];
	int			size;
	int			end_idx;

	if ((fd < 0 || fd > 256) || (line == NULL) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[size] = '\0';
		backup[fd] = ft_strjoin(backup[fd], buf);
		if ((end_idx = chk_newline(backup[fd])) >= 0)
		{
			make_line(&backup[fd], line, end_idx);
			return (1);
		}
	}
	return (make_line_chk_eof(&backup[fd], line, size));
}
