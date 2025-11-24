/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:08:24 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/24 09:56:16 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_set_pixel_color_bytes(char *pixel_addr, t_color color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (unsigned int)(ft_clamp(color.x) * 255.0);
	g = (unsigned int)(ft_clamp(color.y) * 255.0);
	b = (unsigned int)(ft_clamp(color.z) * 255.0);
	*(uint32_t *)pixel_addr = (r << 16) | (g << 8) | b;
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
	focal_len = (WIN_WIDTH / 2.0) / tan(cam->fov / 2.0);
	cam->focal_vector = vec3_scale(cam->forward, focal_len);
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
