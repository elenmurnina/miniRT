/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 09:55:18 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 09:55:34 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	sphere_bump(t_object *obj, t_vector *norm, t_vector hit)
{
	t_triple	a;
	t_color		color;

	a.xy = vec_norm(vec_minus((*obj).coord_xyz, (hit)));
	a.fi = 1 * (1 - (atan2((a.xy).y, (a.xy).x) + M_PI) / (2 * M_PI));
	a.pi = 1 * ((2 * asin((a.xy).z) + M_PI) / (2 * M_PI));
	color = get_color(obj->texture_bump, a.fi, a.pi);
	a.x = vec_norm(vec_product_v3(vec_create(0, 0, 1), a.xy));
	a.y = vec_norm(vec_product_v3(a.x, a.xy));
	a.x = vec_mult(a.x, (color.r - 128) / 128.0);
	a.y = vec_mult(a.y, (color.g - 128) / 128.0);
	a.x = vec_plas(a.x, a.y);
	a.x = vec_norm(vec_plas(a.x, *norm));
	return (a.x);
}

void	apply_bmp(t_object *obj, t_vector *norm, t_vector hit)
{
	if (obj->type == SPHERE)
		*norm = sphere_bump(obj, norm, hit);
}
