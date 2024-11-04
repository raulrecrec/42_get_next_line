/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:21:59 by rexposit          #+#    #+#             */
/*   Updated: 2024/11/04 15:36:13 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line_and_update(char **fd_unread)
{
	char	*line;
	char	*newline_pos;
	char	*temp;

	if (!*fd_unread)
		return (NULL);
	newline_pos = ft_strchr(*fd_unread, '\n');
	if (newline_pos)
		line = ft_substr(*fd_unread, 0, newline_pos - *fd_unread + 1);
	else
		line = ft_substr(*fd_unread, 0, ft_strlen(*fd_unread));
	if (line && ft_strlen(line) < ft_strlen(*fd_unread))
	{
		temp = *fd_unread;
		*fd_unread = ft_substr(*fd_unread, ft_strlen(line),
				ft_strlen(*fd_unread) - ft_strlen(line));
		free(temp);
	}
	else
	{
		free(*fd_unread);
		*fd_unread = NULL;
	}
	return (line);
}

static char	*read_append(int fd, char *fd_unread, ssize_t byts_rd, char *temp)
{
	char	fd_read[BUFFER_SIZE + 1];

	while (1)
	{
		byts_rd = read(fd, fd_read, BUFFER_SIZE);
		if (byts_rd < 0)
		{
			free(fd_unread);
			return (NULL);
		}
		if (byts_rd == 0)
			break ;
		fd_read[byts_rd] = '\0';
		if (!fd_unread)
			fd_unread = ft_substr(fd_read, 0, ft_strlen(fd_read));
		else
		{
			temp = fd_unread;
			fd_unread = ft_strjoin(fd_unread, fd_read);
			free(temp);
		}
		if (ft_strchr(fd_unread, '\n'))
			break ;
	}
	return (fd_unread);
}

char	*get_next_line(int fd)
{
	static char	*fd_unread;
	char		*line;

	fd_unread = read_append(fd, fd_unread, 0, 0);
	if (!fd_unread || (read(fd, NULL, 0) == 0
			&& (!fd_unread || fd_unread[0] == '\0')))
	{
		free(fd_unread);
		fd_unread = NULL;
		return (NULL);
	}
	line = extract_line_and_update(&fd_unread);
	return (line);
}
