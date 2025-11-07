/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:49:30 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/07 18:33:59 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_parse_camera(char **line_inputs, int line, t_scene *scene)
{
	t_camera	*camera;
	int			err_code;

	if (scene->camera)
		return (ft_err_line(line, "You must have only one camera"), 2);
	camera = malloc(sizeof(t_camera));
	if (camera == NULL)
		return (perror("error"), 1);
	scene->camera = camera;
	if (ft_str_arraylen(line_inputs) != 4)
		return (ft_err_line(line,
				"Camera needs Coord, Orient and Field of View"), 2);
	err_code = ft_parse_coord(line_inputs[1], line, &camera->coord);
	if (err_code > 0)
		return (err_code);
	err_code = ft_parse_orient(line_inputs[2], line, &camera->orientation);
	if (err_code > 0)
		return (err_code);
	if (ft_parse_integer(line_inputs[3], line,
			"Field of View", &camera->field_of_view))
		return (2);
	return (0);
}

static int	ft_parse_line(char **line_inputs, int line, t_scene *scene)
{
	char	*identifier;

	identifier = line_inputs[0];
	if (identifier == NULL)
		return (0);
	else if (!ft_strcmp(identifier, "C"))
		return (ft_parse_camera(line_inputs, line, scene));
	else if (!ft_strcmp(identifier, "A"))
		return (ft_parse_ambient(line_inputs, line, scene));
	else if (!ft_strcmp(identifier, "L"))
		return (ft_parse_light(line_inputs, line, scene));
	else if (!ft_strcmp(identifier, "pl"))
		return (ft_parse_plane(line_inputs, line, scene));
	else if (!ft_strcmp(identifier, "sp"))
		return (ft_parse_sphere(line_inputs, line, scene));
	else if (!ft_strcmp(identifier, "cy"))
		return (ft_parse_cylinder(line_inputs, line, scene));
	ft_err_line(line, "Incorrect line identifier");
	return (2);
}

static int	ft_validate_scene(t_scene *scene)
{
	int	err_code;

	err_code = 0;
	if (scene->camera == NULL)
	{
		ft_error("You must have a camera");
		err_code = 1;
	}
	if (scene->ambient == NULL)
	{
		ft_error("You must have an ambient lighting");
		err_code = 1;
	}
	if (scene->light == NULL)
	{
		ft_error("You must have a light");
		err_code = 1;
	}
	return (err_code);
}

static int	ft_parse_scene_internal(char **lines, t_scene *scene)
{
	int		err_code;
	int		line_code;
	int		line;
	char	**line_inputs;

	err_code = 0;
	line = 0;
	while (lines[line])
	{
		line_inputs = ft_split(lines[line], ' ');
		if (line_inputs == NULL)
			return (perror("error"), 1);
		line_code = ft_parse_line(line_inputs, line + 1, scene);
		ft_free_str_array(line_inputs);
		if (line_code == 1)
			return (1);
		err_code += line_code;
		line++;
	}
	return (err_code);
}

int	ft_parse_scene(char *filename, t_scene *scene)
{
	int		fd;
	char	**lines;
	int		err_code;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("error"), 1);
	lines = ft_fd_split(fd, '\n');
	close(fd);
	if (lines == NULL)
		return (perror("error"), 1);
	err_code = ft_parse_scene_internal(lines, scene);
	ft_free_str_array(lines);
	if (err_code == 1)
		return (1);
	if (err_code > 1)
	{
		ft_validate_scene(scene);
		return (1);
	}
	return (ft_validate_scene(scene));
}
