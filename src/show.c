/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:33:26 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/19 15:44:29 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_close(t_mlx_data *mlx_data)
{
	mlx_destroy_image(mlx_data->mlx, mlx_data->img->inner);
	mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	mlx_destroy_display(mlx_data->mlx);
	free(mlx_data->mlx);
	exit(0);
	return (0);
}

static int	ft_on_expose(t_mlx_data *mlx_data)
{
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win,
		mlx_data->img->inner, 0, 0);
	return (0);
}

static int	ft_on_keydown(int keycode, t_mlx_data *mlx_data)
{
	if (keycode == 65307)
		ft_close(mlx_data);
	return (0);
}

int	ft_show_image(void *mlx, t_image *img)
{
	void		*win;
	t_mlx_data	mlx_data;

	win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (win == NULL)
	{
		perror("error");
		return (1);
	}
	mlx_put_image_to_window(mlx, win, img->inner, 0, 0);
	mlx_data.mlx = mlx;
	mlx_data.img = img;
	mlx_data.win = win;
	mlx_hook(win, 2, 1L << 0, ft_on_keydown, &mlx_data);
	mlx_hook(win, 12, 1L << 15, ft_on_expose, &mlx_data);
	mlx_hook(win, 17, 0, ft_close, &mlx_data);
	mlx_loop(mlx);
	return (0);
}
