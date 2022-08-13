/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersept_cylin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:42:56 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 10:43:33 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	intersept_circle(t_object sph, t_vector loook, t_vector cam, t_point *point)
{
	double		dist1;
	t_vector	lk;
	t_vector	c;

	c = vec_plas(sph.coord_xyz, vec_mult(sph.vec_3d_norm, sph.height));
	if (vect_mod(vec_minus(cam, c)) > vect_mod(vec_minus(cam, sph.coord_xyz)))
		c = sph.coord_xyz;
	lk = vec_norm(loook);
	sph.vec_3d_norm = vec_norm(sph.vec_3d_norm);
	dist1 = vec_product_v2(sph.vec_3d_norm, vec_minus(c, cam))
		/ vec_product_v2(sph.vec_3d_norm, lk);
	if (fabs(vec_product_v2(sph.vec_3d_norm, lk)) < 0.00000000001)
		return (FALSE);
	if (dist1 < 0.0000001)
		return (FALSE);
	if (vect_mod(vec_minus(vec_plas(cam, vec_mult(lk, dist1)), c))
		> sph.radius)
		return (FALSE);
	point->dist = dist1;
	if (vec_product_v2(sph.vec_3d_norm, loook) > 0)
		point->norm = vec_minus(vec_create(0, 0, 0), sph.vec_3d_norm);
	else
		point->norm = sph.vec_3d_norm;
	point->hit = vec_plas(cam, vec_mult(lk, dist1));
	return (TRUE);
}

double	dist_plane(t_vector a, t_vector plane, t_vector norm)
{
	double	d;

	norm = vec_norm(norm);
	d = norm.x * plane.x + norm.y * plane.y + norm.z * plane.z;
	return (norm.x * a.x + norm.y * a.y + norm.z * a.z - d);
}

int	cyl2(t_vector cam, t_triple tr, t_point *point, t_object sph)
{	
	t_vector	hitt;
	t_vector	b;
	t_vector	nor;

	hitt = vec_plas(cam, vec_mult(tr.loook, tr.pi));
	if (intersept_circle(sph, tr.loook, cam, point))
	{
		if (point->dist > tr.pi && dist_plane(hitt, tr.xy, sph.vec_3d_norm)
			* dist_plane(hitt, sph.coord_xyz, sph.vec_3d_norm) > 0)
			return (TRUE);
		if (point->dist < tr.pi)
			return (TRUE);
	}
	if (dist_plane(hitt, tr.xy, sph.vec_3d_norm) * dist_plane(hitt,
			sph.coord_xyz, sph.vec_3d_norm) < 0)
	{
		point->dist = tr.pi;
		point->hit = hitt;
		b = vec_minus(point->hit, sph.coord_xyz);
		nor = vec_mult(sph.vec_3d_norm, vec_product_v2(b, sph.vec_3d_norm));
		point->norm = vec_norm(vec_minus(b, nor));
		return (TRUE);
	}
	return (FALSE);
}

int	intersept_cylinder(t_object sph, t_vector lok, t_vector cam, t_point *point)
{
	t_triple	tr;
	t_vector	d1;

	sph.vec_3d_norm = vec_norm(sph.vec_3d_norm);
	tr.loook = lok;
	tr.xy = vec_plas(sph.coord_xyz, vec_mult(sph.vec_3d_norm, sph.height));
	tr.exp = dist(lok, cam, sph.vec_3d_norm, sph.coord_xyz);
	if (tr.exp > sph.radius)
		return (FALSE);
	tr.x = vec_minus(lok, vec_mult(sph.vec_3d_norm, vec_product_v2(lok,
					sph.vec_3d_norm)));
	tr.y = vec_mult(sph.vec_3d_norm, vec_product_v2(vec_minus(cam,
					sph.coord_xyz), sph.vec_3d_norm));
	tr.y = vec_minus(cam, tr.y);
	d1 = circle(sph.coord_xyz, sph.radius, tr.y, tr.x);
	if (vec_product_v2(tr.x, tr.x) == 0)
		return (intersept_circle(sph, lok, cam, point));
	tr.pi = vec_product_v2(vec_minus(d1, tr.y), tr.x)
		/ vec_product_v2(tr.x, tr.x);
	if (tr.pi < 0)
		return (FALSE);
	return (cyl2(cam, tr, point, sph));
}

int	intersept_trian(t_object sph, t_vector loook, t_vector cam, t_point *point)
{
	t_triple	a;
	double		u;
	double		v;

	a.x = vec_minus(sph.triangle_vertices[1], sph.triangle_vertices[0]);
	a.y = vec_minus(sph.triangle_vertices[2], sph.triangle_vertices[0]);
	a.exp = vec_product_v2(a.x, vec_product_v3(loook, a.y));
	if (fabs(a.exp) < 0.0001)
		return (FALSE);
	a.xy = vec_minus(cam, sph.triangle_vertices[0]);
	u = vec_product_v2(a.xy, vec_product_v3(loook, a.y)) * (1.0 / a.exp);
	if (u < 0.0 || u > 1.0)
		return (FALSE);
	a.loook = vec_product_v3(a.xy, a.x);
	v = vec_product_v2(loook, a.loook) * (1.0 / a.exp);
	if (v < 0.0 || u + v > 1.0)
		return (FALSE);
	point->dist = vec_product_v2(a.y, a.loook) * (1.0 / a.exp);
	if (point->dist < 0)
		return (FALSE);
	point->norm = vec_norm(vec_product_v3(a.x, a.y));
	if (vec_product_v2(point->norm, loook) > 0)
		point->norm = vec_minus(vec_create(0, 0, 0), point->norm);
	point->hit = vec_plas(cam, vec_mult(loook, point->dist));
	return (TRUE);
}
