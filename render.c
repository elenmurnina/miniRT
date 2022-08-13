/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:39:51 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 10:54:07 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	paint_big_pixel(t_mystr *myst, int x, int y, int color)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (a < PRESIGION)
	{
		while (b < PRESIGION)
		{
			my_mlx_pixel_put(myst->im, x + a, y + b, color);
			b++;
		}
		b = 0;
		a++;
	}		
}

t_vector	create_look(t_global *global, int x, int y)
{
	t_vector	a;
	t_vector	b;

	a = vec_mult(global->cam_x,
			tan(((double)global->fov_cam) / 180.0)
			* ((double)(x - HEIGHT / 2)) / (double) WIDTH);
	b = vec_mult(global->cam_y, tan(((double)global->fov_cam) / 180.0)
			* ((double)(WIDTH / 2 - y)) / (double) WIDTH);
	return (vec_norm(vec_plas(vec_plas(a, b), global->cam_norm_vec)));
}

int	render_next_frame(t_mystr *myst, t_global *global)
{
	int		x;
	int		y;

	y = 0;
	x = 0;
	while (x < HEIGHT)
	{
		while (y < WIDTH)
		{
			paint_big_pixel(myst, x, y, rbg(intersept_object(global,
						global->cam, create_look(global, x, y),
						DEEP_REFLECTION)));
			y += PRESIGION;
		}
		x += PRESIGION;
		if (x % 150 == 0)
			printf(" %d / %d \n", x, HEIGHT);
		y = 0;
	}
	mlx_put_image_to_window(myst->mlx, myst->win,
		(myst->im)->img, 0, 0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

double	ft_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
