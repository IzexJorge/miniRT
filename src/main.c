/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:06:09 by jescuder          #+#    #+#             */
/*   Updated: 2025/10/30 14:51:24 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_free_scene(t_scene *scene)
{
	free(scene->camera);
	free(scene->ambient);
	free(scene->light);
	free(scene->planes);
	free(scene->spheres);
	free(scene->cylinders);
	return (1);
}

static int	ft_free_mlx(void *mlx_ptr, void *img_ptr)
{
	if (mlx_ptr)
	{
		if (img_ptr)
			mlx_destroy_image(mlx_ptr, img_ptr);
		mlx_destroy_display(mlx_ptr);
	}
	return (1);
}

static int	ft_free_all(t_scene *scene, void *mlx_ptr, void *img_ptr)
{
	ft_free_scene(scene);
	ft_free_mlx(mlx_ptr, img_ptr);
	return (1);
}

static int	ft_init_mlx(void **mlx_ptr, void **img_ptr)
{
	*mlx_ptr = mlx_init();
	if (*mlx_ptr == NULL)
	{
		*img_ptr = NULL;
		perror("error");
		return (0);
	}
	*img_ptr = mlx_new_image(mlx_ptr, 1920, 1080);
	if (*img_ptr == NULL)
	{
		perror("error");
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_scene		scene;
	void		*mlx_ptr;
	void		*img_ptr;

	if (argc != 2)
	{
		ft_putendl_fd("There must only be a .rt file as argument.", STDERR_FILENO);
		return (1);
	}
	ft_memset(&scene, 0, sizeof(t_scene));
	if (ft_parse_scene(argv[1], &scene) == 0)
		return (ft_free_scene(&scene));
	if (ft_init_mlx(&mlx_ptr, &img_ptr) == 0)
		return (ft_free_all(&scene, mlx_ptr, img_ptr));
	if (ft_render_image(&scene, img_ptr) == 0)
		return (ft_free_all(&scene, mlx_ptr, img_ptr));
	ft_free_scene(&scene);
	if (ft_show_image(mlx_ptr, img_ptr) == 0)
		return (ft_free_mlx(mlx_ptr, img_ptr));
	ft_free_mlx(mlx_ptr, img_ptr);
	return (0);
}
