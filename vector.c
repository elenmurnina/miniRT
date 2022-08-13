/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:22:26 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 10:25:14 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	vect_mod(t_vector a)
{
	double	all;

	all = a.x * a.x + a.y * a.y + a.z * a.z;
	all = sqrt(all);
	return (all);
}

t_vector	vec_plas(t_vector a, t_vector b)
{
	t_vector	out;

	out.x = a.x + b.x ;
	out.y = a.y + b.y;
	out.z = a.z + b.z;
	return (out);
}

t_vector	vec_minus(t_vector a, t_vector b)
{
	t_vector	out;

	out.x = a.x - b.x ;
	out.y = a.y - b.y;
	out.z = a.z - b.z;
	return (out);
}

t_vector	vec_norm(t_vector a)
{
	double	f;

	f = vect_mod(a);
	a.x = a.x / f;
	a.y = a.y / f;
	a.z = a.z / f;
	return (a);
}

t_vector	vec_mult(t_vector a, double f)
{
	a.x = a.x * f;
	a.y = a.y * f;
	a.z = a.z * f;
	return (a);
}
