/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:08:24 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/14 01:17:32 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	ft_shade(t_ray ray, t_scene *scene, t_hitpoint *hit)
{
	t_color	color;
	t_vec3	light_dir;
	t_vec3	amb_light;
	double	intensity;

	(void)ray;/* Ambient contribution */
	amb_light = vec3_scale(scene->ambient->color, scene->ambient->ratio);
	color = vec3_mul(hit->color, amb_light);

	/* Diffuse contribution from the first light */
	light_dir = vec3_normalize(vec3_sub(scene->light->coord, hit->point));
	intensity = ft_clamp(vec3_dot(hit->normal, light_dir)) * scene->light->ratio;
	color.x += hit->color.x * intensity;
	color.y += hit->color.y * intensity;
	color.z += hit->color.z * intensity;

	/* Clamp final color to [0,1] */
	color.x = ft_clamp(color.x);
	color.y = ft_clamp(color.y);
	color.z = ft_clamp(color.z);

	return (color);
}

t_color	ft_trace_ray(t_ray ray, t_scene *scene)
{
	t_color	color;
	t_hitpoint	hit;
	double	min_t;

	min_t = DBL_MAX;
	hit.type = 0;
	hit.point = (t_vec3){0.0, 0.0, 0.0};
	hit.normal = (t_vec3){0.0, 0.0, 0.0};
	hit.t = 0.0;
	ft_search_spheres(ray, scene, &min_t, &hit);
	if (hit.type != 0)
		color = ft_shade(ray, scene, &hit);
	else
		color = vec3_scale(scene->ambient->color, scene->ambient->ratio);
	return (color);
}

t_color	ft_get_pixel_color(int x, int y, t_scene *scene)
{
	t_ray	ray;

	ray.origin = scene->camera->coord;
	ray.dir = ft_get_ray_direction(x, y, scene->camera);
	if (x == WIN_WIDTH / 2 && y == WIN_HEIGHT / 2)
		printf("ray dir: %f %f %f\n", ray.dir.x, ray.dir.y, ray.dir.z);
	return (ft_trace_ray(ray, scene));
}

void	ft_set_pixel_color_bytes(char *pixel_addr, t_color color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (unsigned int)(ft_clamp(color.x) * 255.0);
	g = (unsigned int)(ft_clamp(color.y) * 255.0);
	b = (unsigned int)(ft_clamp(color.z) * 255.0);
	*(uint32_t *)pixel_addr = (r << 16) | (g << 8) | b;
}

void	ft_render_image(t_image *img, t_scene *scene)
{
	int		y;
	int		x;
	char	*pixel_addr;
	int		bytes_per_pixel;

	pixel_addr = img->data;
	bytes_per_pixel = img->bits_per_pixel / 8;
	ft_init_camera(scene->camera);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ft_set_pixel_color_bytes(pixel_addr,
				ft_get_pixel_color(x, y, scene));
			pixel_addr += bytes_per_pixel;
			x++;
		}
		y++;
	}
}
