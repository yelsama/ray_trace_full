/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:12:09 by mohouhou          #+#    #+#             */
/*   Updated: 2023/06/18 17:26:54 by mohouhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

char	*get_line(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	ret = gl_substr(str, 0, i);
	return (ret);
}

char	*read_str(char	*str, int fd)
{
	int		size;
	char	*part;
	size_t	malloc_size;

	size = -100;
	malloc_size = BUFFER_SIZE;
	while ((size == BUFFER_SIZE && !gl_strchr(str, '\n')) || size == -100)
	{
		part = (char *)malloc(sizeof(char) * (malloc_size + 1));
		if (!part)
			return (NULL);
		size = read(fd, part, BUFFER_SIZE);
		if (size == -1)
		{
			free (part);
			return (NULL);
		}
		part[size] = '\0';
		str = gl_strjoin(str, part);
		free(part);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	char		*ret;
	static char	*s;
	int			i;
	int			size;
	char		*tmp;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = read_str(s, fd);
	if (!tmp)
		return (NULL);
	ret = get_line(tmp);
	i = gl_strlen2(ret);
	size = gl_strlen2(tmp);
	s = gl_substr(tmp, i, size);
	if (!s || s[0] == '\0')
	{
		free(s);
		s = NULL;
	}
	free(tmp);
	return (ret);
}
