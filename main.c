/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 04:58:14 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 10:47:41 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//int test_color = 0;

int	rotate(int button, int x1, int y1, t_global *global)
{
	t_vector	a3;
	t_vector	loook;
	t_point		temp;

	if (global->a->flag == 1)
		return (0);
	a3 = vec_plas(vec_mult(global->cam_x, tan(((double)global->fov_cam) / 180.0)
				*((double)(x1 - HEIGHT / 2)) / (double) WIDTH), vec_mult(
				global->cam_y, tan(((double)global->fov_cam) / 180.0)
				* ((double)(WIDTH / 2 - y1)) / (double) WIDTH));
	if (button == 2)
	{
		loook = vec_norm(vec_plas(a3, global->cam_norm_vec));
		global->moved_obj = intersept_objet0(global->start, loook,
				global->cam, &temp);
		return (0);
	}
	global->cam_norm_vec = vec_norm(vec_plas(a3, global->cam_norm_vec));
	global->cam_y = vec_norm(vec_minus(global->cam_y, vec_mult(
					global->cam_norm_vec, vec_product_v2(
						global->cam_norm_vec, global->cam_y))));
	global->cam_x = vec_norm(vec_product_v3(global->cam_norm_vec,
				global->cam_y));
	global->a->flag = 1;
	return (0);
}

void	cam_init(t_global *global, t_mystr *a)
{
	t_vector	x;
	t_vector	temp;

	if (fabs(vec_product_v2(global->cam_norm_vec, vec_create(0, 0, 1)))
		> fabs(vec_product_v2(global->cam_norm_vec, vec_create(0, 1, 0))))
		x = vec_create(0, 1, 0);
	else
		x = vec_create(0, 0, 1);
	temp = vec_mult(global->cam_norm_vec, vec_product_v2(
				global->cam_norm_vec, x));
	global->cam_y = vec_norm(vec_minus(x, temp));
	global->cam_x = vec_norm(vec_product_v3(global->cam_norm_vec,
				global->cam_y));
	mlx_key_hook(a->win, key_hook, global);
	mlx_hook(a->win, 17, 0, ft_exit, global);
	mlx_mouse_hook(a->win, rotate, global);
	mlx_loop_hook(a->mlx, ft_loop, global);
	render_next_frame(a, global);
	mlx_loop(a->mlx);
}

int	ft_exit(t_global *global)
{
	free_global(global);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data		im;
	t_mystr		a;
	t_global	global;

	if (argc != 2)
	{
		printf("wrong_ARG\n");
		return (0);
	}
	global_init(&global, &a);
	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, HEIGHT, WIDTH, "miniRT");
	im.img = mlx_new_image(a.mlx, HEIGHT, WIDTH);
	im.addr = mlx_get_data_addr(im.img, &im.bits_per_pixel,
			&im.line_length, &im.endian);
	a.im = &im;
	parsing_read_scene(argv[1], &global);
	cam_init(&global, &a);
	free_global(&global);
	return (0);
}
