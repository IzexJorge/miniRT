/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:33:25 by jose-jim          #+#    #+#             */
/*   Updated: 2025/11/14 22:39:24 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

void	ft_search_planes(t_ray ray, t_scene *scene, double *min_t, t_hitpoint *hit)
{
	t_plane	*pl;
	t_list	*node;
	double	t;

	if (scene->num_planes == 0)
		return ;
	node = scene->planes;
	while (node)
	{
		pl = node->content;
		if (ft_intersect_plane(ray, pl, &t)
			&& ft_is_less(t, *min_t))
		{
			*min_t = t;
			hit->type = 'p';
			hit->point = vec3_add(ray.origin, vec3_scale(ray.dir, t));
			hit->normal = vec3_normalize(pl->orient);
			hit->t = t;
			hit->color = pl->color;
		}
		node = node->next;
	}
}