/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:15:33 by kkleinsc          #+#    #+#             */
/*   Updated: 2022/04/20 16:25:38 by kkleinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*gnl_create(int *len)
{
	*len = 1;
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*out;
	static char	red[4096][BUFFER_SIZE + 1];
	int			len;

	if (fd < 0 || fd > 4096)
		return (NULL);
	out = gnl_create(&len);
	while (len != 0)
	{
		if (!*red[fd])
		{
			len = read(fd, red[fd], BUFFER_SIZE);
			if (len == -1)
				return (NULL);
		}
		else
		{
			len = search_str(red[fd], '\n');
			out = stradd(out, red[fd], len);
			if (red[fd][len - 1] == '\n')
				len = 0;
			strcut(red[fd]);
		}
	}
	return (out);
}
