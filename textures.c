/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 04:06:23 by hregina           #+#    #+#             */
/*   Updated: 2022/08/09 10:53:24 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_texture(t_global *rt, t_texture **texture, char *file_name)
{
	if (file_name != NULL)
	{
		(*texture) = (t_texture *)malloc(sizeof(t_texture));
		if (!(*texture))
			minirt_error("Error malloc: t_texture *texture");
		(*texture)->ptr = mlx_xpm_file_to_image(rt->a->mlx, file_name,
				&(*texture)->width, &(*texture)->height);
		if (!(*texture)->ptr)
			minirt_error("Error creating texture");
		(*texture)->img = mlx_get_data_addr((*texture)->ptr, &(*texture)->bpp,
				&(*texture)->size_line, &(*texture)->endian);
		if (!(*texture)->img)
			minirt_error("Error creating texture");
	}
}

t_color	get_color(t_texture *texture, double fi, double pi)
{
	int		index;
	t_color	color;

	index = (int)(texture->height * pi) * texture->size_line
		+ texture->bpp / 8 * (int)(texture->width * fi);
	color.b = (unsigned char)texture->img[index + 0];
	color.g = (unsigned char)texture->img[index + 1];
	color.r = (unsigned char)texture->img[index + 2];
	return (color);
}

t_light	*create_light(t_vector A, t_color b, double power)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		minirt_error("Error malloc: t_light *light");
	light->vec.x = A.x;
	light->vec.y = A.y;
	light->vec.z = A.z;
	light->color = b;
	light->power = power;
	return (light);
}
