/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_read_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 03:38:19 by hregina           #+#    #+#             */
/*   Updated: 2022/07/24 10:19:30 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static int	open_file(char *file)
{
	int	len;
	int	fd;

	len = ft_strlen(file);
	if (len < 4 || ft_strcmp(file + len - 3, ".rt"))
		minirt_error("Error scene: file-scene name incorrect");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		minirt_error("Error scene: cannot open file-scene");
	return (fd);
}

void	parsing_read_scene(char *scene_file, t_global *global)
{
	char	*line;
	int		rd;
	int		fd;

	line = NULL;
	rd = 1;
	fd = open_file(scene_file);
	while (rd)
	{
		rd = get_next_line(fd, &line);
		if (rd < 0)
			minirt_error("Error scene: cannot read file scene");
		if (rd == 0 && !line)
			break ;
		if (ft_strncmp(line, "#", 1))
			parsing_element(line, global);
		free(line);
	}
	if (close(fd) < 0)
		minirt_error("Error scene: cannot close file scene");
	if (global->_a == 0 || global->_c == 0)
		minirt_error("Error scene: not enough information");
}
