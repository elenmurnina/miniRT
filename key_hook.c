/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:00:07 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 10:36:18 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	key_hook4(int key, t_global *global)
{
	if (key == 257)
		global->cam = vec_plas(global->cam, global->cam_y);
	else if (key == 256)
		global->cam = vec_minus(global->cam, global->cam_y);
	else if (key == 30 && global->moved_obj != 0)
		global->moved_obj->coord_xyz = vec_plas(
				global->moved_obj->coord_xyz, vec_create(0, 0, 1));
	else if (key == 25 && global->moved_obj != 0)
		global->moved_obj->height += 1 ;
	else if (key == 33 && global->moved_obj != 0)
		global->moved_obj->coord_xyz = vec_plas(
				global->moved_obj->coord_xyz, vec_create(0, 1, 0));
	else
		return (0);
	global->a->flag = 1;
	return (0);
}

int	key_hook3(int key, t_global *global)
{
	if (key == 42 && global->moved_obj != 0)
		global->moved_obj->coord_xyz = vec_plas(
				global->moved_obj->coord_xyz, vec_create(0, 0, -1));
	else if (key == 24 && global->moved_obj != 0)
		global->moved_obj->radius += 1 ;
	else if (key == 27 && global->moved_obj != 0)
	{
		global->moved_obj->radius -= 1 ;
		if (global->moved_obj->radius < 0)
			global->moved_obj->radius = 0;
	}
	else if (key == 29 && global->moved_obj != 0)
	{
		global->moved_obj->height -= 1 ;
		if (global->moved_obj->height < 0)
			global->moved_obj->height = 0;
	}
	else if (key == 53)
		ft_exit(global);
	else
		return (key_hook4(key, global));
	global->a->flag = 1;
	return (0);
}

int	key_hook2(int key, t_global *global)
{
	if (key == 35 && global->moved_obj != 0)
		global->moved_obj->coord_xyz = vec_plas(global->moved_obj->coord_xyz,
				vec_create(1, 0, 0));
	else if (key == 91 && global->moved_obj != 0)
		global->moved_obj->vec_3d_norm = rotat_y(
				global->moved_obj->vec_3d_norm, 0.2);
	else if (key == 87 && global->moved_obj != 0)
		global->moved_obj->vec_3d_norm = rotat_y(
				global->moved_obj->vec_3d_norm, -0.2);
	else if (key == 92 && global->moved_obj != 0)
		global->moved_obj->vec_3d_norm = rotat_z(
				global->moved_obj->vec_3d_norm, 0.2);
	else if (key == 88 && global->moved_obj != 0)
		global->moved_obj->vec_3d_norm = rotat_z(
				global->moved_obj->vec_3d_norm, -0.2);
	else if (key == 41 && global->moved_obj != 0)
		global->moved_obj->coord_xyz = vec_plas(
				global->moved_obj->coord_xyz, vec_create(-1, 0, 0));
	else if (key == 39 && global->moved_obj != 0)
		global->moved_obj->coord_xyz = vec_plas(
				global->moved_obj->coord_xyz, vec_create(0, -1, 0));
	else
		return (key_hook3(key, global));
	global->a->flag = 1;
	return (0);
}

int	key_hook(int key, t_global *global)
{
	if (global->a->flag == 1)
		return (0);
	if (key == 13)
		global->cam = vec_plas(global->cam, global->cam_norm_vec);
	else if (key == 1)
		global->cam = vec_minus(global->cam, global->cam_norm_vec);
	else if (key == 2)
		global->cam = vec_plas(global->cam, global->cam_x);
	else if (key == 0)
		global->cam = vec_minus(global->cam, global->cam_x);
	else if (key == 30 && global->moved_obj != 0)
		global->moved_obj->coord_xyz = vec_plas(
				global->moved_obj->coord_xyz, vec_create(0, 0, 1));
	else if (key == 89 && global->moved_obj != 0)
		global->moved_obj->vec_3d_norm = rotat_x(
				global->moved_obj->vec_3d_norm, 0.2);
	else if (key == 86 && global->moved_obj != 0)
		global->moved_obj->vec_3d_norm = rotat_x(
				global->moved_obj->vec_3d_norm, -0.2);
	else
		return (key_hook2(key, global));
	global->a->flag = 1;
	return (0);
}
