/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 23:16:31 by jose-jim          #+#    #+#             */
/*   Updated: 2025/11/11 23:44:51 by jose-jim         ###   ########.fr       */
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
	cam->right = vec3_normalize(vec3_cross(cam->forward, world_up));
	cam->up = vec3_cross(cam->right, cam->forward);
	cam->focal_len = (WIN_WIDTH / 2.0)
		/ tan((cam->field_of_view * M_PI / 180.0) / 2.0);
}

t_vec3	get_ray_direction(int x, int y, t_camera *cam)
{
	t_vec3	dir;
	double	x_cam;
	double	y_cam;

	x_cam = (x + 0.5) - (WIN_WIDTH / 2.0);
	y_cam = (WIN_HEIGHT / 2.0) - (y + 0.5);
	dir = vec3_add(
			vec3_scale(cam->right, x_cam),
			vec3_add(vec3_scale(cam->up, y_cam),
				vec3_scale(cam->forward, -cam->focal_len)));
	return (vec3_normalize(dir));
}
