/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:33:25 by jose-jim          #+#    #+#             */
/*   Updated: 2025/11/18 00:33:50 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	intersect_disk(t_ray ray, t_cylinder *cy, t_vec3 center, double *t)
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

int	ft_intersect_plane(t_ray ray, t_plane *pl, double *t)
{
	double	denom;
	t_vec3	p0r0;

	denom = vec3_dot(pl->orient, ray.dir);
	if (fabs(denom) > EPSILON)
	{
		p0r0 = vec3_sub(pl->coord, ray.origin);
		*t = vec3_dot(p0r0, pl->orient) / denom;
		return (ft_is_greater_equal(*t, 0.0));
	}
	return (0);
}

void	ft_search_planes(t_ray ray, t_scene *scene, double *min_t, t_hit *hit)
{
	t_plane	*pl;
	t_list	*node;
	double	t;
	t_vec3	n;

	node = scene->planes;
	while (node)
	{
		pl = node->content;
		if (ft_intersect_plane(ray, pl, &t) && t < *min_t)
		{
			*min_t = t;
			hit->type = 'p';
			hit->point = vec3_add(ray.origin, vec3_scale(ray.dir, t));
			n = vec3_normalize(pl->orient);
			if (vec3_dot(n, ray.dir) > 0)
				n = vec3_scale(n, -1);
			hit->normal = n;
			hit->t = t;
			hit->color = pl->color;
			if (scene->shadow_mode)
				return ;
		}
		node = node->next;
	}
}
