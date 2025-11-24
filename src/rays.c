/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 23:16:31 by jose-jim          #+#    #+#             */
/*   Updated: 2025/11/24 10:02:13 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_is_shadowed(t_hit hit, t_scene *scene)
{
	t_ray	shadow;
	t_hit	cast;
	double	maxdist;

	shadow.dir = vec3_normalize(vec3_sub(scene->light->coord, hit.point));
	shadow.origin = vec3_add(hit.point, vec3_scale(hit.normal, SHADOW_BIAS));
	maxdist = vec3_length(vec3_sub(scene->light->coord, hit.point));
	cast.type = 0;
	cast.t = 0;
	scene->shadow_mode = 1;
	ft_search_planes(shadow, scene, &maxdist, &cast);
	ft_search_spheres(shadow, scene, &maxdist, &cast);
	ft_search_cyl(shadow, scene, &maxdist, &cast);
	scene->shadow_mode = 0;
	return (cast.type != 0);
}

static t_color	ft_shade(t_ray ray, t_scene *scene, t_hit *hit)
{
	int		is_shadowed;
	t_color	color;
	t_vec3	light_dir;
	t_vec3	amb_light;
	double	intensity;

	(void)ray;
	amb_light = vec3_scale(scene->ambient->color, scene->ambient->ratio);
	color = vec3_mul(hit->color, amb_light);
	light_dir = vec3_normalize(vec3_sub(scene->light->coord, hit->point));
	intensity = ft_clamp(vec3_dot(hit->normal,
				light_dir)) * scene->light->ratio;
	is_shadowed = ft_is_shadowed(*hit, scene);
	color.x += hit->color.x * intensity * !is_shadowed;
	color.y += hit->color.y * intensity * !is_shadowed;
	color.z += hit->color.z * intensity * !is_shadowed;
	return (color);
}

static t_color	ft_trace_ray(t_ray ray, t_scene *scene)
{
	t_color	color;
	t_hit	hit;
	double	min_t;

	min_t = DBL_MAX;
	hit.type = 0;
	hit.point = (t_vec3){0.0, 0.0, 0.0};
	hit.normal = (t_vec3){0.0, 0.0, 0.0};
	hit.t = 0.0;
	scene->shadow_mode = 0;
	ft_search_planes(ray, scene, &min_t, &hit);
	ft_search_spheres(ray, scene, &min_t, &hit);
	ft_search_cyl(ray, scene, &min_t, &hit);
	if (hit.type != 0)
		color = ft_shade(ray, scene, &hit);
	else
		color = vec3_scale(scene->ambient->color, scene->ambient->ratio);
	return (color);
}

t_color	ft_get_pixel_color(double img_x, double img_y, t_scene *scene)
{
	double		x_center_offset;
	double		y_center_offset;
	t_camera	*cam;
	t_vec3		dir;
	t_ray		ray;

	x_center_offset = (img_x - (WIN_WIDTH / 2.0));
	y_center_offset = ((WIN_HEIGHT / 2.0) - img_y);
	cam = scene->camera;
	ray.origin = cam->coord;
	dir = vec3_add(vec3_scale(cam->right, x_center_offset),
			vec3_add(vec3_scale(cam->up, y_center_offset),
				cam->focal_vector));
	ray.dir = vec3_normalize(dir);
	return (ft_trace_ray(ray, scene));
}
