/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:09:36 by rexposit          #+#    #+#             */
/*   Updated: 2024/10/23 18:21:26 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef FD_MAX
#  define FD_MAX FOPEN_MAX
# endif

# if FD_MAX > FOPEN_MAX
#  undef FD_MAX
#  define FD_MAX FOPEN_MAX
# endif

# if FD_MAX < 1
#  undef FD_MAX
#  define FD_MAX FOPEN_MAX
# endif

# ifndef BUFFER_SIZE
# define BUFFER_SIZE BUFSIZ
# endif

# if BUFFER_SIZE > 1000000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

# if BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

char	*get_next_line(int fd);

#endif