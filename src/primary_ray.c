/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 23:16:31 by jose-jim          #+#    #+#             */
/*   Updated: 2025/11/14 01:21:19 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_init_camera(t_camera *cam)
{
	t_vec3	world_up;

	world_up = (t_vec3){0, 1, 0};
	cam->forward = vec3_normalize(cam->orientation);
	if (fabs(vec3_dot(cam->forward, world_up)) > 0.999)
		world_up = (t_vec3){1, 0, 0};
	cam->right = vec3_normalize(vec3_cross(world_up, cam->forward));
	cam->up = vec3_cross(cam->forward, cam->right);
	cam->fov_rad = (cam->fov * M_PI) / 180.0;
	cam->focal_len = (WIN_WIDTH / 2.0) / tan(cam->fov_rad / 2.0);
	printf ("CAMERA TAN FOV: %f\n", tan((cam->fov_rad / 2.0) * 10));
	printf("Camera Focal Length: %f\n", cam->focal_len);
}

t_vec3	ft_get_ray_direction(int x, int y, t_camera *cam)
{
	t_vec3	dir;
	t_vec3	right_scaled;
	t_vec3	up_scaled;
	t_vec3	forward_scaled;
	double	x_cam;
	double	y_cam;

	x_cam = (x + 0.5) - (WIN_WIDTH / 2.0);
	y_cam = (WIN_HEIGHT / 2.0) - (y + 0.5);
	right_scaled = vec3_scale(cam->right, x_cam);
	up_scaled = vec3_scale(cam->up, y_cam);
	forward_scaled = vec3_scale(cam->forward, cam->focal_len);
	dir = vec3_add(right_scaled, vec3_add(up_scaled, forward_scaled));
	return (vec3_normalize(dir));
}

