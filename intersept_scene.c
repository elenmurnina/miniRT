/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersept_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:47:25 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 10:53:41 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	intersept_all_object(t_object sph, t_vector loook, t_vector cam,
	t_point *point)
{
	loook = vec_norm(loook);
	if (sph.type == SPHERE)
		return (intersept_sphere(sph, loook, cam, point));
	if (sph.type == PLANE)
		return (intersept_plane(sph, loook, cam, point));
	if (sph.type == TRIANGLE)
		return (intersept_trian(sph, loook, cam, point));
	if (sph.type == CYLINDER)
		return (intersept_cylinder(sph, loook, cam, point));
	return (FALSE);
}

t_object	*intersept_objet0(t_list *i, t_vector loook, t_vector cam,
			t_point *point)
{
	double		min_dist;
	t_object	*obj;
	t_point		temp;

	min_dist = 9999939990999999999599999999199999999900.0;
	obj = 0;
	while (i != 0)
	{	
		if (intersept_all_object(*(i->a), loook, cam, &temp))
		{
			if (temp.dist < min_dist)
			{
				obj = i->a;
				point->dist = temp.dist;
				point->hit = temp.hit;
				point->norm = temp.norm;
				point->color = ((t_object *)i->a)->color;
				min_dist = temp.dist;
			}
		}
		i = i->next;
	}
	return (obj);
}

void	applay(t_object *obj, t_point *point, t_color *color)
{
	if (obj->checker_board)
		checkerboard(*obj, point->hit, color);
	if (obj->file_text_name)
		apply_textures(*obj, point->hit, color);
	if (obj->file_bump_name)
		apply_bmp(obj, &(point->norm), point->hit);
}

t_color	intersept_object(t_global *global, t_vector cam,
		t_vector loook, int deep)
{
	t_color		color;
	t_point		point;
	t_object	*obj;
	t_triple	trip;

	obj = intersept_objet0(global->start, loook, cam, &point);
	color = point.color;
	if (obj == 0)
		return (global->fon.color);
	applay(obj, &point, &color);
	trip.exp = 100;
	if (obj != 0 && obj->specular == 1 && deep != 0)
	{
		trip.exp = 1000;
		trip.ref = intersept_object(global, vec_plas(point.hit,
					vec_mult(point.norm, 0.001)), vec_reflect(point.norm,
					loook), deep - 1);
	}
	trip.loook = loook;
	phong(global, point, &trip);
	return (final_color(&trip, color, obj->specular));
}
