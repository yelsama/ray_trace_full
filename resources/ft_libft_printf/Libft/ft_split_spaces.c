/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:11:24 by mohouhou          #+#    #+#             */
/*   Updated: 2023/08/20 17:19:54 by mohouhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static char	*split_strings(const char *s)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && !isspace((unsigned char)s[i]))
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (0);
	i = 0;
	while (s[i] != '\0' && !ft_isspace((unsigned char)s[i]))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	count_strings(const char *s)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (!isspace((unsigned char)s[i])
			&& (isspace((unsigned char)s[i + 1]) || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

char	**ft_split_whitespace(const char *s)
{
	char	**p;
	int		words;
	int		i;
	bool	inside_word;

	words = count_strings(s);
	p = malloc(sizeof(char *) * (words + 1));
	if (!p)
		return (0);
	i = 0;
	inside_word = false;
	while (*s)
	{
		if (*s && !inside_word && !isspace((unsigned char)*s))
		{
			p[i] = split_strings(s);
			i++;
			inside_word = true;
		}
		else if (isspace((unsigned char)*s))
			inside_word = false;
		s++;
	}
	p[i] = 0;
	return (p);
}
