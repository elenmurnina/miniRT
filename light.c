/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:46:04 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 10:54:00 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	phong_init(t_triple *trip, t_global *global)
{
	trip->diffuse = create_color(0, 0, 0);
	trip->specular = create_color(0, 0, 0);
	trip->diffuse.r += global->diffuse.power * global->diffuse.color.r / 255.0;
	trip->diffuse.b += global->diffuse.power * global->diffuse.color.b / 255.0;
	trip->diffuse.g += global->diffuse.power * global->diffuse.color.g / 255.0;
}

void	add_diffuse(t_triple *trip, t_light *light, t_point point)
{
	t_vector	vlight;
	double		refl;

	vlight = vec_minus(light->vec, point.hit);
	refl = ft_max(0.0, vec_product_v2(vec_norm(vlight),
				point.norm));
	trip->diffuse.r += refl * light->power * light->color.r / 255.0 * 0.5;
	trip->diffuse.b += refl * light->power * light->color.b / 255.0 * 0.5;
	trip->diffuse.g += refl * light->power * light->color.g / 255.0 * 0.5;
}

void	add_spec(t_triple *trip, t_light *light, t_point point)
{
	double		blic;
	t_vector	vlight;

	vlight = vec_minus(light->vec, point.hit);
	blic = powf(ft_max(0.0, vec_product_v2(vec_norm(point.norm),
					vec_norm(vec_minus(vec_norm(vlight),
							vec_norm(trip->loook))))), trip->exp);
	trip->specular.r += blic * light->power * light->color.r / 255.0 * 0.5;
	trip->specular.b += blic * light->power * light->color.b / 255.0 * 0.5;
	trip->specular.g += blic * light->power * light->color.g / 255.0 * 0.5;
}

void	phong(t_global *global, t_point point, t_triple *trip)
{
	t_list_light	*lights;
	t_point			temp;
	t_vector		vlight;

	lights = global->start_light;
	phong_init(trip, global);
	while (lights != 0)
	{
		vlight = vec_minus(lights->l->vec, point.hit);
		if (intersept_objet0(global->start, vec_norm(vlight), vec_plas(
					point.hit, vec_mult(point.norm, 0.0000001)), &temp) != 0)
		{
			if (temp.dist < vect_mod(vlight) - 0.001)
			{
				lights = lights->next;
				continue ;
			}
		}
		add_diffuse(trip, lights->l, point);
		add_spec(trip, lights->l, point);
		lights = lights->next;
	}
}

t_color	final_color(t_triple *trip, t_color color, int a)
{
	t_color	temp;
	t_color	ret;

	if (a == 1)
	{
		temp = color_mult(color, trip->specular);
		color = color_add(trip->ref, create_color(3, 3, 3));
		color = color_add(color, temp);
		color = color_norm(color);
		return (color);
	}
	ret = color_mult(color, trip->diffuse);
	ret = color_add(ret, color_mult(color, trip->specular));
	ret = color_norm(ret);
	return (ret);
}
