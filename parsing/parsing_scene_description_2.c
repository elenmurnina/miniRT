/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_description_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 03:36:21 by hregina           #+#    #+#             */
/*   Updated: 2022/07/24 08:59:58 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

char	*return_name_file_tex(char **s)
{
	char	*file_name_texture;

	file_name_texture = NULL;
	if ((ft_strcmp(s[0], "pl") == 0 || ft_strcmp(s[0], "sp") == 0)
		&& s[4] && ft_strcmp(s[4], "CB") != 0 && ft_strcmp(s[4], "SR") != 0)
		file_name_texture = s[4];
	if (ft_strcmp(s[0], "cy") == 0 && s[6]
		&& ft_strcmp(s[6], "CB") != 0 && ft_strcmp(s[6], "SR") != 0)
		file_name_texture = s[6];
	if (file_name_texture != NULL)
		return (ft_strdup(file_name_texture));
	else
		return (NULL);
}

char	*return_name_file_bump(char **s)
{
	char	*file_name_bump;

	file_name_bump = NULL;
	if ((ft_strcmp(s[0], "pl") == 0 || ft_strcmp(s[0], "sp") == 0) \
		&& s[4] && s[5] && ft_strcmp(s[5], "CB") != 0 \
		&& ft_strcmp(s[5], "SR") != 0)
		file_name_bump = s[5];
	if (ft_strcmp(s[0], "cy") == 0 && s[6] && s[7]
		&& ft_strcmp(s[7], "CB") != 0 && ft_strcmp(s[7], "SR") != 0)
		file_name_bump = s[7];
	if (file_name_bump != NULL)
		return (ft_strdup(file_name_bump));
	else
		return (NULL);
}

int	check_tex(char *name_file_texture)
{
	size_t	len;

	len = ft_strlen(name_file_texture);
	if (len < 4 || ft_strcmp(name_file_texture + len - 4, ".xpm"))
		minirt_error("Error scene: file-texture name incorrect");
	if (access(name_file_texture, 0))
		minirt_error("Error scene: file-texture not found");
	return (TRUE);
}
