/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:15:32 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/24 08:46:52 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_parse_ambient(char **line_inputs, int line, t_scene *scene)
{
	t_ambient	*ambient;
	int			err_code;

	if (scene->ambient)
		return (ft_err_line(line, "You must have only one ambient"), 2);
	ambient = malloc(sizeof(t_ambient));
	if (ambient == NULL)
		return (perror("error"), 1);
	scene->ambient = ambient;
	if (ft_str_arraylen(line_inputs) != 3)
		return (ft_err_line(line, "Ambient needs Ratio and Color"), 2);
	if (ft_parse_decimal(line_inputs[1], line, "Ratio", &ambient->ratio))
		return (2);
	err_code = ft_parse_color(line_inputs[2], line, &ambient->color);
	if (err_code > 0)
		return (err_code);
	return (0);
}

int	ft_parse_light(char **line_inputs, int line, t_scene *scene)
{
	t_light		*light;
	int			err_code;

	if (scene->light)
		return (ft_err_line(line, "You must have only one light"), 2);
	light = malloc(sizeof(t_light));
	if (light == NULL)
		return (perror("error"), 1);
	scene->light = light;
	if (ft_str_arraylen(line_inputs) != 3)
		return (ft_err_line(line, "Light needs Coord and Ratio"), 2);
	err_code = ft_parse_coord(line_inputs[1], line, &light->coord);
	if (err_code > 0)
		return (err_code);
	if (ft_parse_decimal(line_inputs[2], line, "Ratio", &light->ratio))
		return (2);
	return (0);
}

int	ft_parse_plane(char **line_inputs, int line, t_scene *scene)
{
	t_plane		*plane;
	int			err_code;

	if (ft_str_arraylen(line_inputs) != 4)
		return (ft_err_line(line, "Plane needs Coord, Orient and Color"), 2);
	plane = malloc(sizeof(t_plane));
	if (ft_lstnew_add_front(&scene->planes, plane) == NULL)
		return (perror("error"), 0);
	err_code = ft_parse_coord(line_inputs[1], line, &plane->coord);
	if (err_code > 0)
		return (err_code);
	err_code = ft_parse_orient(line_inputs[2], line, &plane->normal);
	if (err_code > 0)
		return (err_code);
	err_code = ft_parse_color(line_inputs[3], line, &plane->color);
	if (err_code > 0)
		return (err_code);
	scene->num_planes++;
	return (0);
}

int	ft_parse_sphere(char **line_inputs, int line, t_scene *scene)
{
	t_sphere	*sphere;
	int			err_code;

	if (ft_str_arraylen(line_inputs) != 4)
		return (ft_err_line(line, "Sphere needs Coord, Diameter and Color"), 2);
	sphere = malloc(sizeof(t_sphere));
	if (ft_lstnew_add_front(&scene->spheres, sphere) == NULL)
		return (perror("error"), 0);
	err_code = ft_parse_coord(line_inputs[1], line, &sphere->coord);
	if (err_code > 0)
		return (err_code);
	if (ft_parse_decimal(line_inputs[2], line, "Diameter", &sphere->diameter))
		return (2);
	err_code = ft_parse_color(line_inputs[3], line, &sphere->color);
	if (err_code > 0)
		return (err_code);
	scene->num_spheres++;
	return (0);
}

int	ft_parse_cylinder(char **line_inputs, int line, t_scene *scene)
{
	t_cylinder	*cylinder;
	int			err_code;

	if (ft_str_arraylen(line_inputs) != 6)
		return (ft_err_line(line,
				"Cylinder needs Coord, Orient, Diameter, Height and Color"), 2);
	cylinder = malloc(sizeof(t_cylinder));
	if (ft_lstnew_add_front(&scene->cylinders, cylinder) == NULL)
		return (perror("error"), 0);
	err_code = ft_parse_coord(line_inputs[1], line, &cylinder->coord);
	if (err_code > 0)
		return (err_code);
	err_code = ft_parse_orient(line_inputs[2], line, &cylinder->axis);
	if (err_code > 0)
		return (err_code);
	if (ft_parse_decimal(line_inputs[3], line, "Diameter", &cylinder->diameter))
		return (2);
	if (ft_parse_decimal(line_inputs[4], line, "Height", &cylinder->height))
		return (2);
	err_code = ft_parse_color(line_inputs[5], line, &cylinder->color);
	if (err_code > 0)
		return (err_code);
	scene->num_cylinders++;
	return (0);
}
