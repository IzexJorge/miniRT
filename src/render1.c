/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:08:24 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/08 18:43:45 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// static unsigned int	ft_get_pixel_color(
// 						t_vec3 coord, t_vec3 orient, t_scene *scene)
// {
	

// }

static void	ft_render_pixel(char *pixel_addr, int x, int y, t_scene *scene)
{
	(void)pixel_addr;
	(void)x;
	(void)y;
	(void)scene;
	//*(uint32_t *)pixel_addr = ft_get_pixel_color();
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
			ft_render_pixel(pixel_addr, x, y, scene);
			pixel_addr += bytes_per_pixel;
			x++;
		}
		y++;
	}
}
