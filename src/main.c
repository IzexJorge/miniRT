/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:06:09 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/19 15:33:59 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_free_scene(t_scene *scene)
{
	free(scene->camera);
	free(scene->ambient);
	free(scene->light);
	ft_lstclear(&scene->planes, free);
	ft_lstclear(&scene->spheres, free);
	ft_lstclear(&scene->cylinders, free);
}

static void	ft_free_mlx(void *mlx, t_image *img)
{
	if (!mlx)
		return ;
	if (img->inner)
		mlx_destroy_image(mlx, img->inner);
	mlx_destroy_display(mlx);
	free(mlx);
}

static void	ft_free_all(t_scene *scene, void *mlx, t_image *img)
{
	ft_free_scene(scene);
	ft_free_mlx(mlx, img);
}

static int	ft_init_mlx(void **mlx, t_image *img)
{
	*mlx = mlx_init();
	if (*mlx == NULL)
	{
		img->inner = NULL;
		if (errno)
			perror("error");
		else
			ft_err("mlx_init failed");
		return (1);
	}
	img->inner = mlx_new_image(*mlx, WIN_WIDTH, WIN_HEIGHT);
	if (img->inner == NULL)
	{
		if (errno)
			perror("error");
		else
			ft_err("mlx_new_image failed");
		return (1);
	}
	img->data = mlx_get_data_addr(
			img->inner, &img->bits_per_pixel, &img->line_bytes, &img->endian);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_scene		scene;
	void		*mlx;
	t_image		img;

	if (argc != 2)
	{
		ft_err("The only argument must be a .rt file");
		return (1);
	}
	ft_memset(&scene, 0, sizeof(t_scene));
	if (ft_parse_scene(argv[1], &scene))
		return (ft_free_scene(&scene), 1);
	ft_debug(&scene);//TODO QUITAR Provisional, para parseo.
	if (ft_init_mlx(&mlx, &img))
		return (ft_free_all(&scene, mlx, &img), 1);
	ft_render_image(&img, &scene);
	ft_free_scene(&scene);
	if (ft_show_image(mlx, &img))
		return (ft_free_mlx(mlx, &img), 1);
	ft_free_mlx(mlx, &img);
	return (0);
}
