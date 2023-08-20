/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 21:58:05 by ymohamed          #+#    #+#             */
/*   Updated: 2023/08/20 17:18:53 by mohouhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft_printf.h"

void	ft_printhexp(size_t val, char *base, int *n)
{
	if (val > 15)
	{
		*n = *n + 1;
		ft_printhexp(val / 16, base, n);
	}
	write(1, &base[val % 16], 1);
}

void	ft_printhex(unsigned int val, char *base, int *n)
{
	if (val > 15)
	{
		*n = *n + 1;
		ft_printhex(val / 16, base, n);
	}
	write(1, &base[val % 16], 1);
}
