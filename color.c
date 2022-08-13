/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 09:56:21 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 09:58:56 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	color_multd(t_color a, double f)
{
	a.r = a.r * f;
	a.g = a.g * f;
	a.b = a.b * f;
	return (a);
}

t_color	color_add(t_color a, t_color b)
{
	a.r = (a.r) + b.r;
	a.b = (a.b) + b.b;
	a.g = (a.g) + b.g;
	return (a);
}

t_color	color_mult(t_color a, t_color b)
{
	a.r = (a.r) * b.r;
	a.b = (a.b) * b.b;
	a.g = (a.g) * b.g;
	return (a);
}

t_color	color_norm(t_color a)
{
	double	max;

	max = a.r;
	if (max < a.b)
		max = a.b;
	if (max < a.g)
		max = a.g;
	if (max > 255.0)
	{
		a.r = a.r * (255.0 / max);
		a.b = a.b * (255.0 / max);
		a.g = a.g * (255.0 / max);
	}
	return (a);
}

int	rbg(t_color a)
{
	return (256 * 256 * (int)(a.r) + 256 * (int)(a.g) + (int)(a.b));
}
