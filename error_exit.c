/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 03:39:24 by hregina           #+#    #+#             */
/*   Updated: 2022/07/10 03:39:26 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_global	*manage_global(t_global *global)
{
	static t_global	*static_global = 0;

	if (global)
		static_global = global;
	return (static_global);
}

void	minirt_error(char *error)
{
	free_global(manage_global(0));
	printf("%s\n", error);
	exit(1);
}
