/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:13:37 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 10:18:07 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_loop(t_global *global)
{
	t_mystr	*a;

	a = global->a;
	if (a->flag == 0)
		return (0);
	mlx_clear_window(a->mlx, a->win);
	render_next_frame(a, global);
	a->flag = 0;
	return (0);
}

t_color	create_color(double r, double b, double g)
{
	t_color	a;

	a.r = r;
	a.b = b;
	a.g = g;
	return (a);
}

t_vector	rotat_x(t_vector a, double fi)
{
	t_vector	d;

	d.x = a.x;
	d.y = cos(fi) * a.y - sin(fi) * a.z;
	d.z = sin(fi) * a.y + cos(fi) * a.z;
	return (d);
}

t_vector	rotat_y(t_vector a, double fi)
{
	t_vector	d;

	d.x = cos(fi) * a.x - sin(fi) * a.z;
	d.y = a.y;
	d.z = sin(fi) * a.x + cos(fi) * a.z;
	return (d);
}

t_vector	rotat_z(t_vector a, double fi)
{
	t_vector	d;

	d.x = cos(fi) * a.x - sin(fi) * a.y;
	d.y = sin(fi) * a.x + cos(fi) * a.y;
	d.z = a.z;
	return (d);
}
