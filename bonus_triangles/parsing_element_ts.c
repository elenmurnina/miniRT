/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_element_ts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:03:21 by hregina           #+#    #+#             */
/*   Updated: 2022/07/14 19:47:58 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

int	is_valid_int(char *s)
{
	int	num;

	num = 0;
	while (*s)
	{
		num = num * 10 + *s - '0';
		if (!ft_isdigit(*s) || num > 100000000)
			return (FALSE);
		s++;
	}
	return (TRUE);
}

void	parse_vert(t_vector *verts, int *vert_cnt, char **info)
{
	if (!is_valid_double(info[1]) || !is_valid_double(info[2])
		|| !is_valid_double(info[3]))
		minirt_error("Error scene: wrong doubles ts_info");
	verts[*vert_cnt].x = ft_atod(info[1]);
	verts[*vert_cnt].y = ft_atod(info[2]);
	verts[*vert_cnt].z = ft_atod(info[3]);
	(*vert_cnt)++;
}

void	parse_element_ts(char *s, t_global *global,
		t_vector *verts, int *vert_cnt)
{
	char	**info;
	int		face[3];

	info = ft_split(s, ' ');
	if (!info || !info[0] || !info[1] || !info[2] || !info[3] || info[4])
		minirt_error("Error scene: malloc split line ts_info");
	if (ft_strcmp(info[0], "v") == 0)
		parse_vert(verts, vert_cnt, info);
	else if (ft_strcmp(info[0], "f") == 0)
	{
		if (!is_valid_int(info[1]) || !is_valid_int(info[2])
			|| !is_valid_int(info[3]))
			minirt_error("Error scene: wrong ints ts_info");
		face[0] = ft_atoi(info[1]);
		face[1] = ft_atoi(info[2]);
		face[2] = ft_atoi(info[3]);
		if (face[0] <= 0 || face[0] > *vert_cnt || face[1] <= 0
			|| face[1] > *vert_cnt || face[2] <= 0 || face[2] > *vert_cnt)
			minirt_error("Error scene: wrong indices ts_info");
		add_to_list(&(global->start),
			create_triangle(verts, face, global->sr_file_ts));
	}
	else
		minirt_error("Error scene: invalid element in ts_info");
	ft_free_split(info);
}
