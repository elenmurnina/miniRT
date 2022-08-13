/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 16:43:26 by hregina           #+#    #+#             */
/*   Updated: 2021/09/19 16:43:30 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_pow(double nb, double pow)
{
	if (pow < 0)
		return (0);
	if (pow == 0)
		return (1);
	return (nb * ft_pow(nb, pow - 1));
}

static long	ft_atol(const char *nptr)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr++ == '-')
			sign *= -1;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res *= 10;
		res += *nptr++ - '0';
	}
	return (res * sign);
}

static int	ft_in_charset(char const c, char const *charset)
{
	int	i_charset;

	i_charset = 0;
	while (charset[i_charset])
	{
		if (c == charset[i_charset++])
			return (1);
	}
	return (0);
}

double	ft_atod(const char *str)
{
	int		decimal_size;
	double	nb;
	int		sign;

	while (ft_in_charset(*str, "\t "))
		str++;
	sign = 1;
	if ((*str == '+' || *str == '-') && *str++ == '-')
		sign *= -1;
	nb = 0;
	nb += ft_atol(str);
	while (*str && ft_in_charset(*str, "0123456789"))
		str++;
	if (*str == '.')
		str++;
	else
		return (nb * sign);
	decimal_size = 0;
	while (ft_in_charset(str[decimal_size], "0123456789"))
		decimal_size++;
	if (decimal_size)
		nb += ft_atol(str) / (ft_pow(10, decimal_size));
	else
		return (nb * sign);
	return (nb * sign);
}
