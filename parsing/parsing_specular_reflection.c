/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_specular_reflection.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 02:47:04 by hregina           #+#    #+#             */
/*   Updated: 2022/07/23 02:47:05 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

int	parsing_specular_reflection(char **s)
{
	if (((ft_strcmp(s[0], "pl") == 0 || ft_strcmp(s[0], "sp") == 0)
			&& s[4] && ft_strcmp(s[4], "SR") == 0)
		|| (ft_strcmp(s[0], "cy") == 0
			&& s[6] && ft_strcmp(s[6], "SR") == 0)
		|| (ft_strcmp(s[0], "ts") == 0
			&& s[2] && ft_strcmp(s[2], "SR") == 0))
		return (TRUE);
	return (FALSE);
}

int	parsing_checker_board(char **s)
{
	if (((ft_strcmp(s[0], "pl") == 0 || ft_strcmp(s[0], "sp") == 0) \
		&& s[4] && ft_strcmp(s[4], "CB") == 0)
		|| (ft_strcmp(s[0], "cy") == 0
			&& s[6] && ft_strcmp(s[6], "CB") == 0)
		|| (ft_strcmp(s[0], "ts") == 0
			&& s[2] && ft_strcmp(s[2], "CB") == 0))
		return (TRUE);
	return (FALSE);
}
