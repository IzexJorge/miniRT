/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:06:09 by jescuder          #+#    #+#             */
/*   Updated: 2025/10/29 16:39:45 by jescuder         ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	t_scene		scene;
	//t_image	image;

	if (argc != 2)
	{
		ft_putendl_fd("There must only be a .rt file as argument.", STDERR_FILENO);
		return (1);
	}
	ft_memset(&scene, 0, sizeof(t_scene));
	if (ft_parse_scene(argv[1], &scene) == 0)
		return (ft_free_scene(&scene));
	// image = ft_render_image(scene);
	// if (image == NULL)
	// 	return (ft_free_scene(&scene));
	// if (ft_show_image(image) == 0)
	// 	return (ft_free_scene(&scene));
	ft_free_scene(&scene);
	return (0);
}
