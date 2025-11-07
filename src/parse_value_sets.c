/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_sets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:06:37 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/07 18:51:47 by jescuder         ###   ########.fr       */
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
	if (ft_parse_integer(values[0], line, "Color", &color->r))
		return (ft_free_str_array(values), 2);
	if (ft_parse_integer(values[1], line, "Color", &color->g))
		return (ft_free_str_array(values), 2);
	if (ft_parse_integer(values[2], line, "Color", &color->b))
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

//TODO Implementar
static int	ft_parse_normalized(t_vec3 *orientation)
{
	(void)orientation;
	return (0);
}

int	ft_parse_orient(char *input, int line, t_vec3 *orientation)
{
	char	**values;

	values = ft_split(input, ',');
	if (values == NULL)
		return (perror("error"), 1);
	if (ft_str_arraylen(values) != 3)
		return (ft_err_free("Orientation needs 3 values", line, values), 2);
	if (ft_parse_decimal(values[0], line, "Orientation", &orientation->x))
		return (ft_free_str_array(values), 2);
	if (ft_parse_decimal(values[1], line, "Orientation", &orientation->y))
		return (ft_free_str_array(values), 2);
	if (ft_parse_decimal(values[2], line, "Orientation", &orientation->z))
		return (ft_free_str_array(values), 2);
	ft_free_str_array(values);
	if (ft_parse_normalized(orientation))
		return (ft_err_line(line, "Orientation needs to be normalized"), 2);
	return (0);
}
