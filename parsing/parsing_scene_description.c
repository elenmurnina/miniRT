/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_description.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 03:36:21 by hregina           #+#    #+#             */
/*   Updated: 2022/07/24 08:59:58 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void	parsing_camera(char **s, t_global *global)
{
	if (global->_c > 0)
		minirt_error("Error scene: double camera");
	if (s[4] || !is_valid_double(s[3]))
		minirt_error("Error scene: wrong Camera format in file");
	global->cam = parsing_coord(s[1]);
	global->cam_norm_vec = parsing_3d_norm_orient_vec(s[2]);
	global->fov_cam = ft_atoi(s[3]);
	if (global->fov_cam < 0 || global->fov_cam > 180)
		minirt_error("Error scene: FOV: Horizontal field of view out of range");
	global->_c++;
}

void	parsing_light(char **s, t_global *global)
{
	t_light		*light;

	if (ft_strcmp(s[0], "A") == 0)
		get_ligth_a(s, global, &light);
	else
		get_light_l(s, &light);
	if (light->power < 0 || light->power > 1)
		minirt_error("Error scene: lighting ratio out of range");
	if (ft_strcmp(s[0], "A") == 0)
	{
		global->diffuse = *light;
		free(light);
	}
	else
		add_to_list_light(&global->start_light, light);
}

void	parsing_object(char **s, t_global *global)
{
	t_object	*obj;

	if (ft_strcmp(s[0], "pl") == 0)
		obj = get_plane_object(s);
	if (ft_strcmp(s[0], "sp") == 0)
		obj = get_sphere_object(s);
	if (ft_strcmp(s[0], "cy") == 0)
		obj = get_cylinder_object(s);
	obj->specular = parsing_specular_reflection(s);
	obj->checker_board = parsing_checker_board(s);
	obj->file_text_name = return_name_file_tex(s);
	obj->file_bump_name = return_name_file_bump(s);
	create_texture(global, &obj->texture, obj->file_text_name);
	create_texture(global, &obj->texture_bump, obj->file_bump_name);
	add_to_list(&(global->start), obj);
}

static int	parsing_check_identifier(char *s)
{
	if (ft_strncmp("A ", s, 2) == 0
		|| ft_strncmp("C ", s, 2) == 0
		|| ft_strncmp("L ", s, 2) == 0
		|| ft_strncmp("sp ", s, 3) == 0
		|| ft_strncmp("pl ", s, 3) == 0
		|| ft_strncmp("cy ", s, 3) == 0
		|| ft_strncmp("con ", s, 4) == 0
		|| ft_strncmp("ts ", s, 3) == 0)
		return (TRUE);
	else
		return (FALSE);
}

void	parsing_element(char *s, t_global *global)
{
	char	**info;

	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	if (parsing_check_identifier(s))
	{
		info = ft_split(s, ' ');
		if (!info)
			minirt_error("Error scene: malloc split line info");
		if (ft_strcmp(info[0], "A") == 0
			|| ft_strcmp(info[0], "L") == 0)
			parsing_light(info, global);
		else if (ft_strcmp(info[0], "C") == 0)
			parsing_camera(info, global);
		else if (ft_strcmp(info[0], "sp") == 0 || ft_strcmp(info[0], "pl") == 0
			|| ft_strcmp(info[0], "cy") == 0 || ft_strcmp(info[0], "con") == 0)
			parsing_object(info, global);
		else if (ft_strcmp(info[0], "ts") == 0)
			parsing_ts(info, global);
		ft_free_split(info);
	}
	else if (*s != '\n' && *s != '\0')
		minirt_error("Error scene: invalid parameters in scene description");
}
