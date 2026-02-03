/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:08:24 by jescuder          #+#    #+#             */
/*   Updated: 2026/02/03 14:10:10 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_set_pixel_color_bytes(char *pixel_addr, t_color color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (unsigned char)(ft_clamp(color.x) * 255.0);
	g = (unsigned char)(ft_clamp(color.y) * 255.0);
	b = (unsigned char)(ft_clamp(color.z) * 255.0);
	pixel_addr[0] = b;
	pixel_addr[1] = g;
	pixel_addr[2] = r;
	pixel_addr[3] = (unsigned char)255;
}

static void	ft_init_camera(t_camera *cam)
{
	t_vec3	world_up;
	double	focal_len;

	world_up = (t_vec3){0, 1, 0};
	if (fabs(vec3_dot(cam->forward, world_up)) > 0.999)
		world_up = (t_vec3){1, 0, 0};
	cam->right = vec3_normalize(vec3_cross(world_up, cam->forward));
	cam->up = vec3_cross(cam->forward, cam->right);
	if (cam->fov < EPSILON)
		cam->fov = EPSILON;
	else if (cam->fov > M_PI - EPSILON)
		cam->fov = M_PI - EPSILON;
	focal_len = (WIN_WIDTH / 2.0) / tan(cam->fov / 2.0);
	cam->focal_vector = vec3_scale(cam->forward, focal_len);
}

void	ft_render_image(t_image *img, t_scene *scene)
{
	int		y;
	int		x;
	char	*pixel_addr;
	int		bytes_per_pixel;

	bytes_per_pixel = img->bits_per_pixel / 8;
	ft_init_camera(scene->camera);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		pixel_addr = img->data + y * img->line_bytes;
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
