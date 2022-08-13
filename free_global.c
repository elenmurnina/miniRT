/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:49:44 by hregina           #+#    #+#             */
/*   Updated: 2022/07/28 01:49:47 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_mystr(t_global *global)
{
	if ((global->a))
	{
		if ((global->a)->im != 0)
			mlx_destroy_image((global->a)->mlx, ((global->a)->im)->img);
		if ((global->a)->win != 0)
			mlx_destroy_window((global->a)->mlx, (global->a)->win);
	}
}

void	free_object_and_texture(t_list *lst, t_global *global)
{
	if (lst)
	{
		if (lst->a->file_text_name != 0 && lst->a->texture->img)
		{
			free(lst->a->file_text_name);
			lst->a->file_text_name = 0;
			mlx_destroy_image(global->a->mlx, lst->a->texture->ptr);
			free(lst->a->texture);
			if (lst->a->file_bump_name != 0)
			{
				free(lst->a->file_bump_name);
				lst->a->file_bump_name = 0;
				free(lst->a->texture_bump);
			}
		}
		free(lst->a);
		lst->a = 0;
		free_object_and_texture(lst->next, global);
		lst->next = 0;
		free(lst);
		lst = 0;
	}
}

void	free_list_light(t_list_light *lst)
{
	if (lst)
	{
		free(lst->l);
		lst->l = 0;
		free_list_light(lst->next);
		lst->next = 0;
		free(lst);
		lst = 0;
	}
}

void	free_global(t_global *global)
{
	if (global)
	{	
		free_mystr(global);
		free_object_and_texture(global->start, global);
		global->start = 0;
		free_list_light(global->start_light);
		global->start_light = 0;
	}
}
