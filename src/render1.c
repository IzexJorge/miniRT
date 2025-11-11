/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:08:24 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/11 23:20:37 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	ft_trace_ray(t_vec3 start, t_vec3 orient, t_scene *scene)
{
	t_color	color;
	(void)start;
	(void)orient;
	(void)scene;
	color.x = 1.0;//Prueba para comprobar que efectivamente todos los píxeles se ponen rojos. Funciona.
	color.y = 0.0;
	color.z = 0.0;
	return (color);
}

static t_color	ft_get_pixel_color(int x, int y, t_scene *scene)
{
	t_vec3	start;
	t_vec3	orient;

	start = scene->camera->coord;
	orient = get_ray_direction(x, y, scene->camera);
	(void)y;
	return (ft_trace_ray(start, orient, scene));
}

static void	set_pixel_color_bytes(char *pixel_addr, t_color color)
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
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			set_pixel_color_bytes(pixel_addr, ft_get_pixel_color(x, y, scene));
			pixel_addr += bytes_per_pixel;
			x++;
		}
		y++;
	}
}
