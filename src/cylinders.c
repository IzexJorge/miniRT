/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:43:21 by jose-jim          #+#    #+#             */
/*   Updated: 2025/11/24 09:32:28 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_inside_height(t_cylinder *cy, t_vec3 hit)
{
	t_vec3	v;
	double	m;

	v = vec3_sub(hit, cy->coord);
	m = vec3_dot(v, cy->axis);
	return (ft_is_greater_equal(m, -cy->height * 0.5)
		&& ft_is_less_equal(m, cy->height * 0.5));
}

static int	intersect_body(t_ray ray, t_cylinder *cy, double *t)
{
	t_vec3	oc;
	t_vec3	hit;
	double	a;
	double	b;
	double	c;

	oc = vec3_sub(ray.origin, cy->coord);
	a = vec3_dot(ray.dir, ray.dir) - pow(vec3_dot(ray.dir, cy->axis), 2);
	b = 2 * (vec3_dot(oc, ray.dir) - vec3_dot(ray.dir, cy->axis)
			* vec3_dot(oc, cy->axis));
	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cy->axis), 2)
		- pow(cy->diameter * 0.5, 2);
	if (!ft_solve_quadratic(a, b, c, t))
		return (0);
	hit = vec3_add(ray.origin, vec3_scale(ray.dir, *t));
	if (!is_inside_height(cy, hit))
		return (0);
	return (1);
}

static int	ft_intersect_cylinder(t_ray ray, t_cylinder *cy, double *t)
{
	double	t_body;
	double	t_cap;
	int		hit;
	t_vec3	top;
	t_vec3	bot;

	top = vec3_add(cy->coord, vec3_scale(cy->axis, cy->height * 0.5));
	bot = vec3_add(cy->coord, vec3_scale(cy->axis, -cy->height * 0.5));
	hit = 0;
	if (intersect_body(ray, cy, &t_body))
	{
		*t = t_body;
		hit = 1;
	}
	if (intersect_disk(ray, cy, top, &t_cap) && (!hit || ft_is_less(t_cap, *t)))
	{
		*t = t_cap;
		hit = 2;
	}
	if (intersect_disk(ray, cy, bot, &t_cap) && (!hit || ft_is_less(t_cap, *t)))
	{
		*t = t_cap;
		hit = 3;
	}
	return (hit);
}

static void	set_cylinder_normal(t_hit *hit, t_cylinder *cy, int type)
{
	double	m;
	t_vec3	proj;
	t_vec3	v;

	if (type == 1)
	{
		v = vec3_sub(hit->point, cy->coord);
		m = vec3_dot(v, cy->axis);
		proj = vec3_add(cy->coord, vec3_scale(cy->axis, m));
		hit->normal = vec3_normalize(vec3_sub(hit->point, proj));
	}
	if (type == 2)
		hit->normal = cy->axis;
	if (type == 3)
		hit->normal = vec3_scale(cy->axis, -1);
}

void	ft_search_cyl(t_ray ray, t_scene *scene, double *min_t, t_hit *hit)
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
			if (scene->shadow_mode)
				return ;
		}
		node = node->next;
	}
}
