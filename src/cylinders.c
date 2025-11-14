/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:43:21 by jose-jim          #+#    #+#             */
/*   Updated: 2025/11/14 22:55:32 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int is_inside_height(t_cylinder *cy, t_vec3 hit)
{
	t_vec3  v;
	double  m;

	v = vec3_sub(hit, cy->coord);
	m = vec3_dot(v, cy->orient);
	return (ft_is_greater_equal(m, -cy->height * 0.5)
		&& ft_is_less_equal(m,  cy->height * 0.5));
}

int	intersect_cap(t_ray ray, t_cylinder *cy, t_vec3 center, double *t)
{
	double	denom;
	double	tmp;
	t_vec3	hit;
	t_vec3	cp;

	denom = vec3_dot(ray.dir, cy->orient);
	if (fabs(denom) < EPSILON)
		return (0);
	tmp = vec3_dot(vec3_sub(center, ray.origin), cy->orient) / denom;
	if (ft_is_less(tmp, 0.0))
		return (0);
	hit = vec3_add(ray.origin, vec3_scale(ray.dir, tmp));
	cp = vec3_sub(hit, center);
	if (vec3_length(cp) <= cy->diameter * 0.5)
	{
		*t = tmp;
		return (1);
	}
	return (0);
}

int	intersect_body(t_ray ray, t_cylinder *cy, double *t)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	t0;
	double	t1;
	t_vec3	hit;

	oc = vec3_sub(ray.origin, cy->coord);
	a = vec3_dot(ray.dir, ray.dir) - pow(vec3_dot(ray.dir, cy->orient), 2);
	b = 2 * (vec3_dot(oc, ray.dir) - vec3_dot(ray.dir, cy->orient)
		* vec3_dot(oc, cy->orient));
	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cy->orient), 2)
		- pow(cy->diameter * 0.5, 2);
	if (!ft_solve_quadratic(a, b, c, &t0, &t1))
		return (0);
	if (ft_is_less(t0, 0.0))
		t0 = t1;
	if (ft_is_less(t0, 0.0))
		return (0);
	hit = vec3_add(ray.origin, vec3_scale(ray.dir, t0));
	if (!is_inside_height(cy, hit))
		return (0);
	*t = t0;
	return (1);
}

int	ft_intersect_cylinder(t_ray ray, t_cylinder *cy, double *t)
{
	double	t_body;
	double	t_cap;
	int		hit;
	t_vec3 top;
	t_vec3 bottom;

	top = vec3_add(cy->coord, vec3_scale(cy->orient, cy->height * 0.5));
	bottom = vec3_add(cy->coord, vec3_scale(cy->orient, -cy->height * 0.5));
	hit = 0;
	if (intersect_body(ray, cy, &t_body))
	{
		*t = t_body;
		hit = 1;
	}
	if (intersect_cap(ray, cy, top, &t_cap) && (!hit || ft_is_less(t_cap, *t)))
	{
		*t = t_cap;
		hit = 2;
	}
	if (intersect_cap(ray, cy, bottom, &t_cap) && (!hit || ft_is_less(t_cap, *t)))
	{
		*t = t_cap;
		hit = 3;
	}
	return (hit);
}

void	set_cylinder_normal(t_hitpoint *hit, t_cylinder *cy, int type)
{
	double	m;
	t_vec3	proj;
	t_vec3	v;

	if (type == 1)
	{
		v = vec3_sub(hit->point, cy->coord);
		m = vec3_dot(v, cy->orient);
		proj = vec3_add(cy->coord, vec3_scale(cy->orient, m));
		hit->normal = vec3_normalize(vec3_sub(hit->point, proj));
	}
	if (type == 2)
		hit->normal = cy->orient;
	if (type == 3)
		hit->normal = vec3_scale(cy->orient, -1);
}

void	ft_search_cyl(t_ray ray, t_scene *scene,
		double *min_t, t_hitpoint *hit)
{
	t_cylinder	*cy;
	t_list		*node;
	double		t;
	int			type;

	node = scene->cylinders;
	while (node)
	{
		cy = node->content;
		type = ft_intersect_cylinder(ray, cy, &t);
		if (type && ft_is_less(t, *min_t))
		{
			*min_t = t;
			hit->type = 'c';
			hit->point = vec3_add(ray.origin, vec3_scale(ray.dir, t));
			hit->color = cy->color;
			hit->t = t;
			set_cylinder_normal(hit, cy, type);
		}
		node = node->next;
	}
}
