/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:21:59 by rexposit          #+#    #+#             */
/*   Updated: 2024/10/25 20:55:12 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*fd_unread;
	char		fd_read[BUFFER_SIZE + 1];
	char		*line_return;
	char		*aux;
	size_t		bytes_read;
	size_t		line_end;
	
	bytes_read = read(fd, fd_read, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);
	fd_read[bytes_read] = '\0';
	if (fd_unread != NULL)
	{
		aux = ft_strjoin(fd_unread, fd_read);
		free (fd_unread);
		fd_unread = aux;
	}
	else
	{
		fd_unread = malloc(bytes_read + 1 * sizeof(char));
		if (fd_unread == NULL)
			return (NULL);
		ft_strlcpy(fd_unread, fd_read, bytes_read + 1);
	}
	char *newline_pos = ft_strchr(fd_unread, '\n');
	if (newline_pos != NULL)
		line_end = (newline_pos - fd_unread) + 1;
	else
		line_end = ft_strlen(fd_unread);
	line_return = ft_substr(fd_unread, 0, line_end);
	if (line_return == NULL)
		return (NULL);
	aux = ft_substr(fd_unread, line_end, ft_strlen(fd_unread) - line_end);
	free (fd_unread);
	fd_unread = aux;
	return (line_return);
}
#include <fcntl.h>

int main() {
    int fd = open("archivo.txt", O_RDONLY);  // Abre el archivo en modo lectura
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s\n", line);  // Usa la línea devuelta por get_next_line
        free(line);  // Libera la memoria de la línea después de usarla
    }

    close(fd);  // Cierra el archivo después de terminar de leer
    return 0;
}
