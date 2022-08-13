/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ts_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:49:23 by hregina           #+#    #+#             */
/*   Updated: 2022/07/17 18:56:59 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static int	open_ts_file(char *file)
{
	int	len;
	int	fd;

	len = ft_strlen(file);
	if (len < 5 || ft_strcmp(file + len - 4, ".obj"))
		minirt_error("Error scene: ts_file name incorrect");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		minirt_error("Error scene: cannot open ts_file");
	return (fd);
}

t_object	*create_triangle(t_vector *verts, int *face, int specular)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		minirt_error("Error malloc: t_object *object");
	object->coord_xyz.x = 0;
	object->coord_xyz.y = 0;
	object->coord_xyz.z = 0;
	object->color.r = 255;
	object->color.g = 255;
	object->color.b = 0;
	object->type = TRIANGLE;
	object->vec_3d_norm.x = isinf(0);
	object->vec_3d_norm.y = isinf(0);
	object->vec_3d_norm.z = isinf(0);
	object->radius = 0;
	object->height = 0;
	object->triangle_vertices[0] = verts[face[0] - 1];
	object->triangle_vertices[1] = verts[face[1] - 1];
	object->triangle_vertices[2] = verts[face[2] - 1];
	object->specular = specular;
	object->file_text_name = NULL;
	object->file_bump_name = NULL;
	return (object);
}

void	read_ts_file(char *file, t_global *global)
{
	char		*line;
	int			rd;
	int			fd;
	t_vector	verts[5000];
	int			vert_cnt;

	line = NULL;
	rd = 1;
	fd = open_ts_file(file);
	vert_cnt = 0;
	while (rd)
	{
		rd = get_next_line(fd, &line);
		if (rd < 0)
			minirt_error("Error scene: cannot read ts_file");
		if (rd == 0 && !line)
			break ;
		parse_element_ts(line, global, verts, &vert_cnt);
		free(line);
	}
	if (close(fd) < 0)
		minirt_error("Error scene: cannot close ts_file");
}

void	parsing_ts(char **s, t_global *global)
{
	if (!s[1] || (s[2] && ft_strcmp(s[2], "SR") != 0))
		minirt_error("Error scene: wrong ts format in file");
	global->sr_file_ts = parsing_specular_reflection(s);
	read_ts_file(s[1], global);
	global->sr_file_ts = FALSE;
}
