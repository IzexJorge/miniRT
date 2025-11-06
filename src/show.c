/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:33:26 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/05 16:29:06 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_close(t_mlx_data *mlx_data)
{
	mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img_ptr);
	mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
	mlx_destroy_display(mlx_data->mlx_ptr);
	exit(0);
	return (0);
}

static int	ft_on_keydown(int keycode, t_mlx_data *mlx_data)
{
	if (keycode == 65307)
		ft_close(mlx_data);
	return (0);
}

int	ft_show_image(void *mlx_ptr, void *img_ptr)
{
	void		*win_ptr;
	t_mlx_data	mlx_data;

	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "miniRT");
	if (win_ptr == NULL)
	{
		perror("error");
		return (1);
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_data.mlx_ptr = mlx_ptr;
	mlx_data.img_ptr = img_ptr;
	mlx_data.win_ptr = win_ptr;
	mlx_hook(win_ptr, 2, 1L << 0, ft_on_keydown, &mlx_data);
	mlx_hook(win_ptr, 17, 0, ft_close, &mlx_data);
	mlx_loop(mlx_ptr);
	return (0);
}
