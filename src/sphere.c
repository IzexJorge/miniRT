/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:49:06 by jose-jim          #+#    #+#             */
/*   Updated: 2025/11/19 14:07:46 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_intersect_sphere(t_ray ray, t_sphere *sp, double *t)
{
	t_vec3	oc;
	double	b;
	double	c;

	oc = vec3_sub(ray.origin, sp->coord);
	b = 2.0 * vec3_dot(oc, ray.dir);
	c = vec3_dot(oc, oc) - (sp->diameter / 2) * (sp->diameter / 2);
	return (ft_solve_quadratic(1, b, c, t));
}

void	ft_search_spheres(t_ray ray, t_scene *scene, double *min_t, t_hit *hit)
{
	t_sphere	*sp;
	t_list		*node;
	double		t;

	if (scene->num_spheres == 0)
		return ;
	node = scene->spheres;
	while (node)
	{
		sp = node->content;
		if (ft_intersect_sphere(ray, sp, &t)
			&& ft_is_less(t, *min_t))
		{
			*min_t = t;
			hit->type = 's';
			hit->point = vec3_add(ray.origin, vec3_scale(ray.dir, t));
			hit->normal = vec3_normalize(vec3_sub(hit->point, sp->coord));
			hit->t = t;
			hit->color = sp->color;
			if (scene->shadow_mode)
				return ;
		}
		node = node->next;
	}
}
