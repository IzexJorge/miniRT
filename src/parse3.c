/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:06:37 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/01 15:41:03 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_parse_coord(t_coord *coord, char *input)
{
	(void)coord;
	(void)input;
	return (1);
}

int	ft_parse_orientation(t_coord *orientation, char *input)//TODO [-1, 1]
{
	(void)orientation;
	(void)input;
	return (1);
}

int	ft_parse_color(t_color *color, char *input)
{
	char	**rgb;
 
	rgb = ft_split(input, ',');
	if (rgb == NULL)
		return (perror("error"), 0);
	if (ft_str_arraylen(rgb) < 3)
		return (ft_error("Not enough commas in a color."), 0);
	if (ft_str_arraylen(rgb) > 3)
		return (ft_error("Too many commas in a color."), 0);
	color->r = ft_atoi(rgb[0]);
	if (color->r < 0 || color->r > 255)
		return (ft_error("Color value is out of range."), 0);
	color->g = ft_atoi(rgb[1]);
	if (color->g < 0 || color->g > 255)
		return (ft_error("Color value is out of range."), 0);
	color->b = ft_atoi(rgb[2]);
	if (color->b < 0 || color->b > 255)
		return (ft_error("Color value is out of range."), 0);
	return (1);
}

int	ft_parse_ratio(float *ratio, char *input)//TODO [0.0, 1.0]
{
	(void)ratio;
	(void)input;
	return (1);
}

int	ft_parse_size(float *size, char *input)
{
	(void)size;
	(void)input;
	return (1);
}



