/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 03:35:45 by hregina           #+#    #+#             */
/*   Updated: 2022/07/25 14:20:36 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

int	is_valid_color(char *color)
{
	int	num;

	num = 0;
	while (*color)
	{
		num = num * 10 + *color - '0';
		if (!ft_isdigit(*color) || num > 255)
			return (FALSE);
		color++;
	}
	return (TRUE);
}

int	is_valid_double(char *d)
{
	int	cnt_dot;

	cnt_dot = 0;
	if (*d == '-')
		d++;
	while (*d)
	{
		if (*d == '.')
			cnt_dot++;
		else if (!ft_isdigit(*d))
			return (FALSE);
		if (cnt_dot > 1)
			return (FALSE);
		d++;
	}
	return (TRUE);
}

t_color	parsing_color(char *s)
{
	char	**color;
	t_color	color_rgb;

	color_rgb.r = 0;
	color_rgb.g = 0;
	color_rgb.b = 0;
	if (s)
	{
		color = ft_split(s, ',');
		if (!color)
			minirt_error("Error split: in parsing color");
		if (color[3])
			minirt_error("Error scene: wrong color format in file");
		if (is_valid_color(color[0]) && is_valid_color(color[1]) && \
			is_valid_color(color[2]))
		{
			color_rgb.r = ft_atod(color[0]);
			color_rgb.g = ft_atod(color[1]);
			color_rgb.b = ft_atod(color[2]);
		}
		else
			minirt_error("Error scene: wrong color");
		ft_free_split(color);
	}
	return (color_rgb);
}

t_vector	parsing_coord(char *s)
{
	char		**coord;
	t_vector	coord_xyz;

	coord_xyz.x = DBL_MAX;
	coord_xyz.y = DBL_MAX;
	coord_xyz.z = DBL_MAX;
	if (s)
	{
		coord = ft_split(s, ',');
		if (!coord)
			minirt_error("Error split: in parsing coordinates");
		if (coord[3])
			minirt_error("Error scene: wrong coordinates format in file");
		if (is_valid_double(coord[0]) && is_valid_double(coord[1]) && \
			is_valid_double(coord[2]))
		{
			coord_xyz.x = ft_atod(coord[0]);
			coord_xyz.y = ft_atod(coord[1]);
			coord_xyz.z = ft_atod(coord[2]);
		}
		else
			minirt_error("Error scene: wrong coordinates");
		ft_free_split(coord);
	}
	return (coord_xyz);
}

t_vector	parsing_3d_norm_orient_vec(char *s)
{
	char		**splited;
	t_vector	norm_or_vec;

	splited = ft_split(s, ',');
	if (!splited)
		minirt_error("Error split: 3d normalized orientation vector");
	if (splited[3])
		minirt_error("Error scene: wrong 3d normalized orient-n vector format");
	if (is_valid_double(splited[0]) && is_valid_double(splited[1]) && \
		is_valid_double(splited[2]))
	{
		norm_or_vec.x = ft_atod(splited[0]);
		norm_or_vec.y = ft_atod(splited[1]);
		norm_or_vec.z = ft_atod(splited[2]);
	}
	else
		minirt_error("Error scene: wrong 3d normalized orientation vector");
	if ((norm_or_vec.x < -1 || norm_or_vec.x > 1)
		|| (norm_or_vec.y < -1 || norm_or_vec.y > 1)
		|| (norm_or_vec.z < -1 || norm_or_vec.z > 1))
		minirt_error("Error scene: 3d normalized orient-n vector out of range");
	if (splited)
		ft_free_split(splited);
	norm_or_vec = vec_norm(norm_or_vec);
	return (norm_or_vec);
}
