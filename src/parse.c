/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:49:30 by jescuder          #+#    #+#             */
/*   Updated: 2025/10/30 10:27:21 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_validate_scene(t_scene *scene)
{
	int	valid;

	valid = 1;
	if (scene->camera == NULL)
	{
		valid = 0;
		ft_putendl_fd("The camera is missing.", STDERR_FILENO);
	}
	if (scene->ambient == NULL)
	{
		valid = 0;
		ft_putendl_fd("The ambient lighting is missing.", STDERR_FILENO);
	}
	if (scene->light == NULL)
	{
		valid = 0;
		ft_putendl_fd("The light is missing.", STDERR_FILENO);
	}
	return (valid);
}

static int	ft_parse_line(char *line, t_scene *scene)
{
	if (line[0] == '\0')
		return (1);
	(void) scene;
	return (0);
}

int	ft_parse_scene(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("input error");
		return (0);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_parse_line(line, scene) == 0)
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
	}
	close(fd);
	return (ft_validate_scene(scene));
}
