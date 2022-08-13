/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:44:52 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 10:51:19 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	sign(double a)
{
	if (a > 0.0)
		return (1);
	return (-1);
}

void	checkerboard_sphere(t_object obj, t_vector hit, t_color *color)
{
	double		fi;
	double		pi;
	t_vector	xy;

	xy = vec_norm(vec_minus(obj.coord_xyz, hit));
	fi = CHECBOARD * (1 - (atan2(xy.y, xy.x) + M_PI) / (2 * M_PI));
	pi = CHECBOARD * ((2 * asin(xy.z) + M_PI) / (2 * M_PI));
	if (sign(sin(fi) * sin(pi)) == 1)
		*color = create_color(0, 200, 0);
	else
		*color = create_color(200, 0, 0);
}

void	checkerboard_cyl(t_object obj, t_vector hit, t_color *color,
		t_triple trip)
{
	double		fi;
	double		pi;
	t_vector	xy;

	xy = vec_minus(hit, obj.coord_xyz);
	fi = 5 * atan2(vec_product_v2(xy, trip.y), vec_product_v2(xy, trip.x));
	if (vec_product_v2(xy, (obj).vec_3d_norm) < 0.00001)
		pi = vect_mod(xy);
	else if (vec_product_v2(xy, (obj).vec_3d_norm) + 0.00001 > (obj).height)
		pi = (obj).height + 2 * (obj).radius - vect_mod(vec_minus(xy,
					vec_mult((obj).vec_3d_norm, (obj).height)));
	else
		pi = (obj).radius + vec_product_v2((obj).vec_3d_norm, xy);
	pi = (pi / ((obj).height + (obj).radius * 2)) * M_PI ;
	if (sign(sin(fi) * sin(pi * 12)) == 1)
		*color = create_color(0, 200, 0);
	else
		*color = create_color(200, 0, 0);
}

void	checkerboard_plane(t_object obj, t_vector hit, t_color *color)
{
	t_triple	tr;
	double		fi;
	double		pi;

	if (fabs(vec_product_v2(obj.vec_3d_norm, vec_create(0, 0, 1)))
		> fabs(vec_product_v2(obj.vec_3d_norm, vec_create(0, 1, 0))))
		tr.x = vec_create(0, 1, 0);
	else
		tr.x = vec_create(0, 0, 1);
	tr.x = vec_norm(vec_minus(tr.x, vec_mult(obj.vec_3d_norm,
					vec_product_v2(obj.vec_3d_norm, tr.x))));
	tr.y = vec_norm(vec_product_v3(obj.vec_3d_norm, tr.x));
	tr.xy = vec_minus(obj.coord_xyz, hit);
	fi = (vec_product_v2(tr.x, tr.xy));
	pi = (vec_product_v2(tr.y, tr.xy));
	if (sign(sin(fi) * sin(pi)) == 1)
		*color = create_color(0, 200, 0);
	else
		*color = create_color(200, 0, 0);
}

void	checkerboard(t_object obj, t_vector hit, t_color *color)
{
	t_triple	triple;

	if (obj.type == SPHERE)
		checkerboard_sphere(obj, hit, color);
	else if (obj.type == CYLINDER)
	{
		(obj).vec_3d_norm = vec_norm((obj).vec_3d_norm);
		if (fabs(vec_product_v2((obj).vec_3d_norm, vec_create(0, 0, 1)))
			> fabs(vec_product_v2((obj).vec_3d_norm, vec_create(0, 1, 0))))
			triple.x = vec_create(0, -1, 0);
		else
			triple.x = vec_create(0, 0, 1);
		triple.x = vec_norm(vec_minus(triple.x, vec_mult((obj).vec_3d_norm,
						vec_product_v2((obj).vec_3d_norm, triple.x))));
		triple.y = vec_norm(vec_product_v3((obj).vec_3d_norm, triple.x));
		checkerboard_cyl(obj, hit, color, triple);
	}
	else if (obj.type == PLANE)
		checkerboard_plane(obj, hit, color);
}
