/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 03:39:35 by hregina           #+#    #+#             */
/*   Updated: 2022/08/09 10:53:18 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_to_list(t_list **start, void *A)
{
	t_list	*i;

	if (*start == 0)
	{
		*start = malloc(sizeof(t_list));
		if (!*start)
			minirt_error("Error malloc: t_list *start");
		(*start)->next = 0;
		(*start)->a = A;
		return ;
	}
	i = *start;
	while (i->next != 0)
		i = i->next;
	i->next = malloc(sizeof(t_list));
	if (!i->next)
		minirt_error("Error malloc: t_list *start");
	i->next->next = 0;
	i->next->a = A;
}

void	add_to_list_light(t_list_light **start, void *L)
{
	t_list_light	*i;

	if (*start == 0)
	{
		*start = malloc(sizeof(t_list_light));
		if (!*start)
			minirt_error("Error malloc: t_list_light *start_light");
		(*start)->next = 0;
		(*start)->l = L;
		return ;
	}
	i = *start;
	while (i->next != 0)
		i = i->next;
	i->next = malloc(sizeof(t_list_light));
	if (!i->next)
		minirt_error("Error malloc: t_list *start");
	i->next->next = 0;
	i->next->l = L;
}

t_object	*create_object(t_vector coord, t_color b, int type)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		minirt_error("Error malloc: t_object *object");
	object->coord_xyz.x = coord.x;
	object->coord_xyz.y = coord.y;
	object->coord_xyz.z = coord.z;
	object->color = b;
	object->type = type;
	object->vec_3d_norm.x = isinf(0);
	object->vec_3d_norm.y = isinf(0);
	object->vec_3d_norm.z = isinf(0);
	object->radius = 0;
	object->height = 0;
	object->specular = FALSE;
	object->checker_board = FALSE;
	return (object);
}

void	a_init(t_mystr *a)
{
	a->flag = 0;
	a->im = 0;
	a->mlx = 0;
	a->win = 0;
}

void	global_init(t_global *global, t_mystr *a)
{
	manage_global(global);
	global->start = 0;
	global->start_light = 0;
	global->_a = 0;
	global->_c = 0;
	global->sr_file_ts = FALSE;
	global->fon.color = create_color(10, 00, 10);
	global->diffuse.color = create_color(0, 0, 0);
	global->diffuse.power = 0;
	global->moved_obj = 0;
	global->cam = vec_create(0, 0, 0);
	global->cam_norm_vec = vec_create(0, 0, -1);
	global->cam_x = vec_create(1, 0, 0);
	global->cam_y = vec_create(0, 1, 0);
	global->a = a;
	a_init(a);
}
