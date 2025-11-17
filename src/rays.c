/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 23:16:31 by jose-jim          #+#    #+#             */
/*   Updated: 2025/11/18 00:10:08 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_init_camera(t_camera *cam)
{
	t_vec3	world_up;

	world_up = (t_vec3){0, 1, 0};
	cam->forward = vec3_normalize(cam->orient);
	if (fabs(vec3_dot(cam->forward, world_up)) > 0.999)
		world_up = (t_vec3){1, 0, 0};
	cam->right = vec3_normalize(vec3_cross(world_up, cam->forward));
	cam->up = vec3_cross(cam->forward, cam->right);
	cam->fov_rad = (cam->fov * M_PI) / 180.0;
	cam->focal_len = (WIN_WIDTH / 2.0) / tan(cam->fov_rad / 2.0);
	printf ("CAMERA TAN FOV: %f\n", tan((cam->fov_rad / 2.0) * 10));
	printf("Camera Focal Length: %f\n", cam->focal_len);
}

t_vec3	ft_cam_ray_direction(int x, int y, t_camera *cam)
{
	double	x_cam;
	double	y_cam;
	t_vec3	dir;

	x_cam = (x + 0.5) - (WIN_WIDTH / 2.0);
	y_cam = (WIN_HEIGHT / 2.0) - (y + 0.5);
	dir = vec3_add(vec3_scale(cam->right, x_cam),
			vec3_add(vec3_scale(cam->up, y_cam),
				vec3_scale(cam->forward, cam->focal_len)));
	return (vec3_normalize(dir));
}

int	ft_is_shadowed(t_hit hit, t_scene *scene)
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
