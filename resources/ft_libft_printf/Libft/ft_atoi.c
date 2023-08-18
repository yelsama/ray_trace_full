/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:30:18 by ymohamed          #+#    #+#             */
/*   Updated: 2023/08/19 02:18:43 by mohouhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	calcu(int *nb, int *md, int *i, char *ptr);

int	ft_atoi(const char *str)
{
	char	*ptr;
	int		i;
	int		sn;
	int		nb;
	int		md;

	ptr = (char *)str;
	i = 0;
	sn = 1;
	nb = 0;
	md = 0;
	while (ptr[i] == ' ' || (ptr[i] > 8 && ptr[i] < 14))
		i++;
	if (ptr[i] == '-' || ptr[i] == '+')
		if (ptr[i++] == '-')
			sn = sn * -1;
	while (ptr[i] == '0')
		i++;
	calcu(&nb, &md, &i, ptr);
	if (md > 19 && sn < 0)
		return (0);
	else if (md > 19 && sn > 0)
		return (-1);
	return (nb * sn);
}

static void	calcu(int *nb, int *md, int *i, char *ptr)
{
	char	*max;
	int		c;
	int		m;

	c = *i;
	m = 0;
	max = "9223372036854775807";
	while (ptr[*i] >= '0' && ptr[*i] <= '9' && *md < 21)
	{
		*nb = *nb * 10 + (ptr[*i] - 48);
		*md = *md + 1;
		*i = *i + 1;
	}
	if (*md == 19)
	{
		while (ptr[c] <= max[m] && m <= 19)
		{
			m++;
			c++;
		}
		if (m < 19)
			*md = 20;
	}
}
