/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:12:29 by mohouhou          #+#    #+#             */
/*   Updated: 2023/06/18 17:27:05 by mohouhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

char	*gl_strchr(const char *s, int c)
{
	char	*d;

	if (!s)
		return (0);
	d = (char *)s;
	while (*d != (unsigned char)c)
	{
		if (*d == '\0')
			return (NULL);
		d++;
	}
	return (d);
}

int	gl_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str != NULL && str[i] != '\0')
		i++;
	return (i);
}

int	gl_strlen2(char *str)
{
	int	i;

	i = 0;
	while (str != NULL && str[i] != '\0')
		i++;
	return (i);
}

char	*gl_strjoin(char *s1, char *s2)
{
	int		size;
	char	*array;
	int		i;
	int		z;

	size = gl_strlen(s1) + gl_strlen(s2);
	if (size == 0)
		return (NULL);
	i = 0;
	array = (char *)malloc(sizeof(char) * (size +1));
	if (array == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		array[i] = s1[i];
		i++;
	}
	z = 0;
	while (s2 && s2[z])
		array[i++] = s2[z++];
	array[i] = '\0';
	free(s1);
	return (array);
}

char	*gl_substr(char *s, int start, int len)
{
	char	*c;
	int		i;
	int		l;

	i = start;
	l = 0;
	if (!s)
		return (NULL);
	if (start >= gl_strlen2(s))
	{
		c = (char *)malloc(sizeof(char));
		if (c == NULL)
			return (NULL);
		c[0] = '\0';
		return (c);
	}
	if (len >= gl_strlen2(s))
		len = gl_strlen2(s) - start;
	c = (char *)malloc(sizeof(char) * (len + 1));
	if (c == NULL)
		return (NULL);
	while (i < (len + start) && s[i])
		c[l++] = s[i++];
	c[l] = '\0';
	return (c);
}
