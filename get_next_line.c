/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:21:59 by rexposit          #+#    #+#             */
/*   Updated: 2024/10/29 19:11:42 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *fd_unread)
{
	char	*line;
	char	*newline_pos = ft_strchr(fd_unread, '\n');

	if (newline_pos)
		line = ft_substr(fd_unread, 0, newline_pos - fd_unread + 1); // Incluye '\n'
	else
		line = ft_substr(fd_unread, 0, ft_strlen(fd_unread)); // Última línea sin '\n'
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*fd_unread;
	char		fd_read[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	char		*temp;
	char		*line;

	while ((bytes_read = read(fd, fd_read, BUFFER_SIZE)) > 0)
	{
		fd_read[bytes_read] = '\0';
		if (fd_unread == NULL)
			fd_unread = ft_substr(fd_read, 0, ft_strlen(fd_read));
		else
		{
			temp = fd_unread;
			fd_unread = ft_strjoin(fd_unread, fd_read);
			free(temp);
		}
		if (ft_strchr(fd_unread, '\n'))
			break;
	}
	if (bytes_read < 0 || (bytes_read == 0 && (!fd_unread || fd_unread[0] == '\0')))
	{
		free(fd_unread);
		fd_unread = NULL;
		return (NULL);
	}
	// Extraer la línea desde fd_unread
	line = extract_line(fd_unread);
	// Actualizar fd_unread para la próxima llamada
	if (line && ft_strlen(line) < ft_strlen(fd_unread))
	{
		temp = fd_unread;
		fd_unread = ft_substr(fd_unread, ft_strlen(line), ft_strlen(fd_unread) - ft_strlen(line));
		free(temp);
	}
	else
	{
		free(fd_unread);
		fd_unread = NULL;
	}
	return (line);
}
