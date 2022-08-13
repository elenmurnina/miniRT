/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina  <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 03:35:45 by hregina           #+#    #+#             */
/*   Updated: 2022/07/25 14:20:36 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

t_object	*get_plane_object(char **s)
{
	t_object	*obj;

	if ((s[4] && ft_strcmp(s[4], "SR") != 0 && ft_strcmp(s[4], "CB") != 0 \
		&& !check_tex(s[4])) || (s[4] && s[5] && !check_tex(s[5]))
		|| (s[4] && s[5] && s[6]))
		minirt_error("Error scene: wrong plane format in file");
	obj = create_object(parsing_coord(s[1]), parsing_color(s[3]), PLANE);
	obj->vec_3d_norm = parsing_3d_norm_orient_vec(s[2]);
	return (obj);
}

t_object	*get_sphere_object(char **s)
{
	t_object	*obj;

	if ((s[4] && ft_strcmp(s[4], "SR") != 0 && ft_strcmp(s[4], "CB") != 0 \
		&& !check_tex(s[4])) || !is_valid_double(s[2]) \
		|| (s[4] && s[5] && !check_tex(s[5])) || (s[4] && s[5] && s[6]))
		minirt_error("Error scene: wrong sphere format in file");
	obj = create_object(parsing_coord(s[1]), parsing_color(s[3]), SPHERE);
	obj->radius = ft_atod(s[2]) / 2;
	return (obj);
}

t_object	*get_cylinder_object(char **s)
{
	t_object	*obj;

	if ((s[6] && ft_strcmp(s[6], "SR") != 0 && ft_strcmp(s[6], "CB") != 0 \
		&& !check_tex(s[6])) || !is_valid_double(s[3]) \
		|| !is_valid_double(s[4]) || (s[6] && s[7] && !check_tex(s[7])) \
		|| (s[6] && s[7] && s[8]))
		minirt_error("Error scene: wrong cylinder format in file");
	obj = create_object(parsing_coord(s[1]), parsing_color(s[5]), CYLINDER);
	obj->vec_3d_norm = parsing_3d_norm_orient_vec(s[2]);
	obj->radius = ft_atod(s[3]) / 2;
	obj->height = ft_atod(s[4]);
	return (obj);
}

void	get_ligth_a(char **s, t_global *global, t_light **light)
{
	double	pow;

	if (global->_a > 0)
		minirt_error("Error scene: double ambient lightning");
	if (s[3] || !is_valid_double(s[1]))
		minirt_error("Error scene: wrong Ambient lightning format in file");
	pow = ft_atod(s[1]);
	(*light) = create_light(parsing_coord(NULL), parsing_color(s[2]), pow);
	global->_a++;
}

void	get_light_l(char **s, t_light **light)
{
	double	pow;

	if ((s[3] && s[4]) || !is_valid_double(s[2]))
		minirt_error("Error scene: wrong Light format in file");
	pow = ft_atod(s[2]);
	(*light) = create_light(parsing_coord(s[1]), parsing_color(s[3]), pow);
}
