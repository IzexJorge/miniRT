/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:15:32 by jescuder          #+#    #+#             */
/*   Updated: 2025/10/31 20:44:01 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_parse_ambient(char **line_input, t_scene *scene)
{
	t_ambient	*ambient;
	char		**line_input;

	if (scene->ambient)
		return (ft_error("There's more than one ambient.", STDERR_FILENO), 0);
	if (ft_str_arraylen(line_input) < 3)
		return (ft_error("Not enough ambient info.", STDERR_FILENO), 0);
	if (ft_str_arraylen(line_input) > 3)
		return (ft_error("Too much ambient info.", STDERR_FILENO), 0);
	ambient = malloc(sizeof(t_ambient));
	if (ambient == NULL)
		return (perror("error"), 0);
	scene->ambient = ambient;
	if (ft_parse_ratio(&ambient->ratio, line_input[1]) == 0)
		return (0);
	if (ft_parse_color(&ambient->color, line_input[2]) == 0)
		return (0);
	return (1);
}

static int	ft_parse_light(char **line_input, t_scene *scene)
{
	t_light	*light;
	char	**line_input;

	if (scene->light)
		return (ft_error("There's more than one light.", STDERR_FILENO), 0);
	if (ft_str_arraylen(line_input) < 3)
		return (ft_error("Not enough light info.", STDERR_FILENO), 0);
	if (ft_str_arraylen(line_input) > 3)
		return (ft_error("Too much light info.", STDERR_FILENO), 0);
	light = malloc(sizeof(t_light));
	if (light == NULL)
		return (perror("error"), 0);
	scene->light = light;
	if (ft_parse_coord(&light->coord, line_input[1]) == 0)
		return (0);
	if (ft_parse_ratio(&light->ratio, line_input[2]) == 0)
		return (0);
	return (1);
}

static int	ft_parse_plane(char **line_input, t_scene *scene)
{
	t_plane	*plane;
	char	**line_input;

	if (ft_str_arraylen(line_input) < 4)
		return (ft_error("Not enough plane info.", STDERR_FILENO), 0);
	if (ft_str_arraylen(line_input) > 4)
		return (ft_error("Too much plane info.", STDERR_FILENO), 0);
	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return (perror("error"), 0);
	if (ft_lstnew_add_front(&scene->planes, plane) == NULL)
		return (perror("error"), 0);
	if (ft_parse_coord(&plane->coord, line_input[1]) == 0)
		return (0);
	if (ft_parse_orientation(&plane->orientation, line_input[2]) == 0)
		return (0);
	if (ft_parse_color(&plane->color, line_input[3]) == 0)
		return (0);
	return (1);
}

static int	ft_parse_sphere(char **line_input, t_scene *scene)
{
	t_sphere	*sphere;
	char		**line_input;

	if (ft_str_arraylen(line_input) < 4)
		return (ft_error("Not enough sphere info.", STDERR_FILENO), 0);
	if (ft_str_arraylen(line_input) > 4)
		return (ft_error("Too much sphere info.", STDERR_FILENO), 0);
	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (perror("error"), 0);
	if (ft_lstnew_add_front(&scene->planes, sphere) == NULL)
		return (perror("error"), 0);
	if (ft_parse_coord(&sphere->coord, line_input[1]) == 0)
		return (0);
	if (ft_parse_size(&sphere->diameter, line_input[2]) == 0)
		return (0);
	if (ft_parse_color(&sphere->color, line_input[3]) == 0)
		return (0);
	return (1);
}

static int	ft_parse_cylinder(char **line_input, t_scene *scene)
{
	t_cylinder	*cylinder;
	char		**line_input;

	if (ft_str_arraylen(line_input) < 6)
		return (ft_error("Not enough cylinder info.", STDERR_FILENO), 0);
	if (ft_str_arraylen(line_input) > 6)
		return (ft_error("Too much cylinder info.", STDERR_FILENO), 0);
	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return (perror("error"), 0);
	if (ft_lstnew_add_front(&scene->planes, cylinder) == NULL)
		return (perror("error"), 0);
	if (ft_parse_coord(&cylinder->coord, line_input[1]) == 0)
		return (0);
	if (ft_parse_orientation(&cylinder->orientation, line_input[2]) == 0)
		return (0);
	if (ft_parse_size(&cylinder->diameter, line_input[3]) == 0)
		return (0);
	if (ft_parse_size(&cylinder->height, line_input[4]) == 0)
		return (0);
	if (ft_parse_color(&cylinder->color, line_input[5]) == 0)
		return (0);
	return (1);
}
