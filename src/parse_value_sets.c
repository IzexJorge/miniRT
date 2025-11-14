/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_sets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:06:37 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/14 22:39:24 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_parse_color(char *input, int line, t_color *color)
{
	char	**values;

	values = ft_split(input, ',');
	if (values == NULL)
		return (perror("error"), 1);
	if (ft_str_arraylen(values) != 3)
		return (ft_err_free("Color needs 3 values", line, values), 2);
	if (ft_parse_color_value(values[0], line, &color->x))
		return (ft_free_str_array(values), 2);
	if (ft_parse_color_value(values[1], line, &color->y))
		return (ft_free_str_array(values), 2);
	if (ft_parse_color_value(values[2], line, &color->z))
		return (ft_free_str_array(values), 2);
	return (ft_free_str_array(values), 0);
}

int	ft_parse_coord(char *input, int line, t_vec3 *coordinates)
{
	char	**values;

	values = ft_split(input, ',');
	if (values == NULL)
		return (perror("error"), 1);
	if (ft_str_arraylen(values) != 3)
		return (ft_err_free("Coordinates need 3 values", line, values), 2);
	if (ft_parse_decimal(values[0], line, "Coordinates", &coordinates->x))
		return (ft_free_str_array(values), 2);
	if (ft_parse_decimal(values[1], line, "Coordinates", &coordinates->y))
		return (ft_free_str_array(values), 2);
	if (ft_parse_decimal(values[2], line, "Coordinates", &coordinates->z))
		return (ft_free_str_array(values), 2);
	return (ft_free_str_array(values), 0);
}

static int	ft_parse_normalized(t_vec3 *orient)
{
	if (ft_is_equal(vec3_length(*orient), 1))
		return (0);
	return (1);
}

int	ft_parse_orient(char *input, int line, t_vec3 *orient)
{
	char	**values;

	values = ft_split(input, ',');
	if (values == NULL)
		return (perror("error"), 1);
	if (ft_str_arraylen(values) != 3)
		return (ft_err_free("Orientation needs 3 values", line, values), 2);
	if (ft_parse_decimal(values[0], line, "Orientation", &orient->x))
		return (ft_free_str_array(values), 2);
	if (ft_parse_decimal(values[1], line, "Orientation", &orient->y))
		return (ft_free_str_array(values), 2);
	if (ft_parse_decimal(values[2], line, "Orientation", &orient->z))
		return (ft_free_str_array(values), 2);
	ft_free_str_array(values);
	if (ft_parse_normalized(orient))
		return (ft_err_line(line, "Orientation is not normalized"), 2);
	return (0);
}
