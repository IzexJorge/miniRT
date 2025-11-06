/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:06:09 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/06 20:21:12 by jescuder         ###   ########.fr       */
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

// static void	ft_free_mlx(void *mlx_ptr, void *img_ptr)
// {
// 	if (mlx_ptr)
// 	{
// 		if (img_ptr)
// 			mlx_destroy_image(mlx_ptr, img_ptr);
// 		mlx_destroy_display(mlx_ptr);
// 	}
// }

// static void	ft_free_all(t_scene *scene, void *mlx_ptr, void *img_ptr)
// {
// 	ft_free_scene(scene);
// 	ft_free_mlx(mlx_ptr, img_ptr);
// }

// static int	ft_init_mlx(void **mlx_ptr, void **img_ptr)
// {
// 	*mlx_ptr = mlx_init();
// 	if (*mlx_ptr == NULL)
// 	{
// 		*img_ptr = NULL;
// 		perror("error");
// 		return (1);
// 	}
// 	*img_ptr = mlx_new_image(mlx_ptr, 1920, 1080);
// 	if (*img_ptr == NULL)
// 	{
// 		perror("error");
// 		return (1);
// 	}
// 	return (0);
// }

int	main(int argc, char *argv[])
{
	t_scene		scene;
	void		*mlx_ptr;
	void		*img_ptr;

	if (argc != 2)
	{
		ft_error("The only argument must be a .rt file.");
		return (1);
	}
	ft_memset(&scene, 0, sizeof(t_scene));
	if (ft_parse_scene(argv[1], &scene))
		return (ft_free_scene(&scene), 1);
	ft_debug(&scene);//Provisional, para parseo. Coménta estas líneas si descomentas algo de abajo.
	ft_free_scene(&scene);
	(void)mlx_ptr;
	(void)img_ptr;
	// if (ft_init_mlx(&mlx_ptr, &img_ptr))
	// 	return (ft_free_all(&scene, mlx_ptr, img_ptr), 1);
	// if (ft_render_image(&scene, img_ptr))
	// 	return (ft_free_all(&scene, mlx_ptr, img_ptr), 1);
	// ft_free_scene(&scene);
	// if (ft_show_image(mlx_ptr, img_ptr))
	// 	return (ft_free_mlx(mlx_ptr, img_ptr), 1);
	// ft_free_mlx(mlx_ptr, img_ptr);
	return (0);
}
