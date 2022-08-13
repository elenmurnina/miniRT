/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersept_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:42:04 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 10:53:54 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	intersept_sphere(t_object sph, t_vector loook, t_vector cam, t_point *point)
{
	t_vector	vpc;
	double		tca;
	double		d2;
	double		thc;

	loook = vec_norm(loook);
	vpc = vec_minus(sph.coord_xyz, cam);
	tca = vec_product_v2(vpc, loook);
	d2 = vec_product_v2(vpc, vpc) - tca * tca;
	if (sph.radius * sph.radius < d2)
		return (FALSE);
	thc = sqrt(sph.radius * sph.radius - d2);
	point->dist = tca - thc;
	if (point->dist < 0)
		point->dist = tca + thc;
	if (point->dist < 0)
		return (FALSE);
	point->hit = vec_plas(cam, vec_mult(loook, point->dist));
	point->norm = vec_norm(vec_minus(point->hit, sph.coord_xyz));
	return (TRUE);
}

int	intersept_plane(t_object sph, t_vector lok, t_vector cam, t_point *point)
{
	double	dist;

	sph.vec_3d_norm = vec_norm(sph.vec_3d_norm);
	lok = vec_norm(lok);
	if (vec_product_v2(sph.vec_3d_norm, lok) == 0)
	{
		point->dist = 99999999999.0;
		if (vec_product_v2(sph.vec_3d_norm, lok) > 0)
			point->norm = vec_minus(vec_create(0, 0, 0), sph.vec_3d_norm);
		else
			point->norm = sph.vec_3d_norm;
		point->hit = vec_plas(cam, vec_mult(lok, point->dist));
		return (TRUE);
	}
	dist = vec_product_v2(sph.vec_3d_norm, vec_minus(sph.coord_xyz, cam))
		/ vec_product_v2(sph.vec_3d_norm, lok);
	if (dist < 0 | dist == 0)
		return (FALSE);
	point->dist = dist;
	if (vec_product_v2(sph.vec_3d_norm, lok) > 0)
		point->norm = vec_minus(vec_create(0, 0, 0), sph.vec_3d_norm);
	else
		point->norm = sph.vec_3d_norm;
	point->hit = vec_plas(cam, vec_mult(lok, dist));
	return (TRUE);
}

double	dist_paralel(t_vector a1, t_vector point1, t_vector point2)
{
	t_vector	ab;
	double		dist;
	t_vector	point3;

	ab = vec_minus(point1, point2);
	dist = vec_product_v2(ab, a1);
	point3 = vec_minus(point1, vec_mult(a1, dist));
	return (vect_mod(vec_minus(point3, point2)));
}

double	dist(t_vector a1, t_vector point1, t_vector a2, t_vector point2)
{
	t_vector	a3;
	double		d;
	double		dist;

	a3 = vec_product_v3(a1, a2);
	if (vect_mod(a3) < 0.0000001)
		return (dist_paralel(a1, point1, point2));
	a3 = vec_norm(a3);
	d = a3.x * point1.x + a3.y * point1.y + a3.z * point1.z;
	dist = a3.x * point2.x + a3.y * point2.y + a3.z * point2.z - d;
	return (ft_max(dist, -dist));
}

t_vector	circle(t_vector sph, double r, t_vector cam, t_vector loook)
{
	t_vector	vpc;
	double		tca;
	double		distanse;
	double		thc;

	loook = vec_norm(loook);
	vpc = vec_minus(sph, cam);
	tca = vec_product_v2(vpc, loook);
	thc = sqrt(r * r - vec_product_v2(vpc, vpc) + tca * tca);
	distanse = tca - thc;
	if (distanse < 0)
		distanse = tca + thc;
	return (vec_plas(cam, vec_mult(loook, distanse)));
}
