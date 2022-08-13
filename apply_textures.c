/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 03:46:04 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 04:47:51 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	sphere_texture_color(t_object *obj, t_vector *hit)
{
	double		fi;
	double		pi;
	t_vector	xy;
	t_color		color;

	xy = vec_norm(vec_minus((*obj).coord_xyz, (*hit)));
	fi = 1 * (1 - (atan2((xy).y, (xy).x) + M_PI) / (2 * M_PI));
	pi = 1 * ((2 * asin((xy).z) + M_PI) / (2 * M_PI));
	color = get_color(obj->texture, fi, pi);
	return (color);
}

t_color	cylindr_texture_color(t_object *obj, t_vector *hit)
{
	t_triple	trip;

	(*obj).vec_3d_norm = vec_norm((*obj).vec_3d_norm);
	if (fabs(vec_product_v2((*obj).vec_3d_norm, vec_create(0, 0, 1))) \
		> fabs(vec_product_v2((*obj).vec_3d_norm, vec_create(0, 1, 0))))
		trip.x = vec_create(0, -1, 0);
	else
		trip.x = vec_create(0, 0, 1);
	trip.x = vec_norm(vec_minus(trip.x, vec_mult((*obj).vec_3d_norm,
					vec_product_v2((*obj).vec_3d_norm, trip.x))));
	trip.y = vec_norm(vec_product_v3((*obj).vec_3d_norm, trip.x));
	trip.xy = vec_minus(*hit, (*obj).coord_xyz);
	trip.fi = 1 * (1 - (atan2(vec_product_v2(trip.xy, trip.y),
					vec_product_v2(trip.xy, trip.x)) + M_PI) / (2 * M_PI));
	if (vec_product_v2(trip.xy, (*obj).vec_3d_norm) < 0.00001)
		trip.pi = vect_mod(trip.xy);
	else if (vec_product_v2(trip.xy, (*obj).vec_3d_norm)
		+ 0.00001 > (*obj).height)
		trip.pi = (*obj).height + 2 * (*obj).radius - vect_mod(vec_minus(
					trip.xy, vec_mult((*obj).vec_3d_norm, (*obj).height)));
	else
		trip.pi = (*obj).radius + vec_product_v2((*obj).vec_3d_norm, trip.xy);
	trip.pi = trip.pi / ((*obj).height + (*obj).radius * 2);
	return (get_color(obj->texture, trip.fi, trip.pi));
}

t_color	plane_texture_color(t_object *obj, t_vector *hit)
{
	double		fi;
	double		pi;
	t_vector	xy;
	t_vector	x;
	t_vector	y;

	if (fabs(vec_product_v2((*obj).vec_3d_norm, vec_create(0, 0, 1))) \
		> fabs(vec_product_v2((*obj).vec_3d_norm, vec_create(0, 1, 0))))
		x = vec_create(0, 1, 0);
	else
		x = vec_create(0, 0, 1);
	x = vec_norm(vec_minus(x, vec_mult((*obj).vec_3d_norm,
					vec_product_v2((*obj).vec_3d_norm, x))));
	y = vec_norm(vec_product_v3((*obj).vec_3d_norm, x));
	xy = vec_minus((*obj).coord_xyz, (*hit));
	fi = (vec_product_v2(x, xy));
	pi = (vec_product_v2(y, xy));
	fi = fabs(fi / 10);
	fi = fi - floor(fi);
	pi = fabs(pi / 10);
	pi = pi - floor(pi);
	return (get_color(obj->texture, fi, pi));
}

void	apply_textures(t_object obj, t_vector hit, t_color *color)
{
	if (obj.type == SPHERE)
		*color = sphere_texture_color(&obj, &hit);
	if (obj.type == CYLINDER)
		*color = cylindr_texture_color(&obj, &hit);
	if (obj.type == PLANE)
		*color = plane_texture_color(&obj, &hit);
}
