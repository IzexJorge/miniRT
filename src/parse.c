/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:49:30 by jescuder          #+#    #+#             */
/*   Updated: 2025/10/31 20:49:06 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_parse_field_of_view(int *field_of_view, char *input)
{
	int	value;

	value = ft_atoi(input);
	if (value >= 0 && value <= 180)
	{
		*field_of_view = value;
		return (1);
	}
	return (0);
}

static int	ft_parse_camera(char **line_input, t_scene *scene)
{
	t_camera	*camera;
	char		**line_input;

	if (scene->camera)
		return (ft_error("There's more than one camera.", STDERR_FILENO), 0);
	if (ft_str_arraylen(line_input) < 4)
		return (ft_error("Not enough camera info.", STDERR_FILENO), 0);
	if (ft_str_arraylen(line_input) > 4)
		return (ft_error("Too much camera info.", STDERR_FILENO), 0);
	camera = malloc(sizeof(t_camera));
	if (camera == NULL)
		return (perror("error"), 0);
	scene->camera = camera;
	if (ft_parse_coord(&camera->coord, line_input[1]) == 0)
		return (free(line_input), 0);
	if (ft_parse_orientation(&camera->orientation, line_input[2]) == 0)
		return (free(line_input), 0);
	if (ft_parse_field_of_view(&camera->field_of_view, line_input[3]) == 0)
		return (free(line_input), 0);
	return (1);
}

static int	ft_parse_line(char **line_input, t_scene *scene)
{
	char	*identifier;

	identifier = line_input[0];
	if (identifier == NULL)
		return (1);
	else if (ft_strcmp(identifier, "C"))
		return (ft_parse_camera(line_input, scene));
	else if (ft_strcmp(identifier, "A"))
		return (ft_parse_ambient(line_input, scene));
	else if (ft_strcmp(identifier, "L"))
		return (ft_parse_light(line_input, scene));
	else if (ft_strcmp(identifier, "pl"))
		return (ft_parse_plane(line_input, scene));
	else if (ft_strcmp(identifier, "sp"))
		return (ft_parse_sphere(line_input, scene));
	else if (ft_strcmp(identifier, "cy"))
		return (ft_parse_cylinder(line_input, scene));
	ft_error("Incorrect line identifier.", STDERR_FILENO);
	return (0);
}

static int	ft_validate_scene(t_scene *scene)
{
	int	valid;

	valid = 1;
	if (scene->camera == NULL)
	{
		valid = 0;
		ft_error("The camera is missing.", STDERR_FILENO);
	}
	if (scene->ambient == NULL)
	{
		valid = 0;
		ft_error("The ambient lighting is missing.", STDERR_FILENO);
	}
	if (scene->light == NULL)
	{
		valid = 0;
		ft_error("The light is missing.", STDERR_FILENO);
	}
	return (valid);
}

int	ft_parse_scene(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;
	char	**line_input;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("error"), 0);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line_input = ft_split(line, '\n');
		free(line);
		if (line_input == NULL)
			return (perror("error"), 0);
		if (ft_parse_line(line_input, scene) == 0)
		{
			ft_free_str_array(line_input);
			return (close(fd), 0);
		}
		ft_free_str_array(line_input);
	}
	close(fd);
	return (ft_validate_scene(scene));
}
