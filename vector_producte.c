/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_producte.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:18:41 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 10:22:07 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	vec_product_v3(t_vector a, t_vector b)
{
	t_vector	out;

	out.x = a.z * b.y - a.y * b.z;
	out.y = a.x * b.z - a.z * b.x;
	out.z = a.y * b.x - a.x * b.y;
	return (out);
}

// t_vector vec_product_v3(t_vector a, t_vector b)
// {
//     t_vector out;
//     out.x = a.y * b.z - a.z * b.y;
//     out.y = a.z * b.x - a.x * b.z;
//     out.z = a.x * b.y - a.y * b.x;
//     return out;
// }

double	vec_product_v2(t_vector a, t_vector b)
{
	double	out;

	out = a.x * b.x + a.y * b.y + a.z * b.z;
	return (out);
}

t_vector	vec_create(double x, double y, double z)
{
	t_vector	f;

	f.x = x;
	f.y = y;
	f.z = z;
	return (f);
}

t_vector	vec_reflect(t_vector a, t_vector b)
{
	t_vector	f;

	f = vec_mult(a, (vec_product_v2(a, b) * 2.0));
	return (vec_minus(b, f));
}
