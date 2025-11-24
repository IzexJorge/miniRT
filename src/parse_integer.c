/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:27:11 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/24 08:56:00 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_get_sign(char **input)
{
	int	sign;

	while (ft_isspace(**input))
		(*input)++;
	if (**input == '-')
	{
		sign = -1;
		(*input)++;
	}
	else
	{
		sign = 1;
		if (**input == '+')
			(*input)++;
	}
	return (sign);
}

static int	ft_parse_integer(char *input, int *var, int min, int max)
{
	int	sign;
	int	result;

	sign = ft_get_sign(&input);
	result = 0;
	while (ft_isdigit(*input))
	{
		result = result * 10.0 + (*input - '0');
		if (result > max)
			return (1);
		input++;
	}
	if (*input != '\0')
		return (2);
	result *= sign;
	if (result < min)
		return (1);
	*var = result;
	return (0);
}

int	ft_parse_field_of_view(char *input, int line, double *fov)
{
	int	var_int;
	int	err_code;

	err_code = ft_parse_integer(input, &var_int, 0, 180);
	if (err_code == 1)
	{
		ft_err_field(line, "Field of View", "Out of range [0, 180]");
		return (2);
	}
	else if (err_code == 2)
	{
		ft_err_field(line, "Field of View", "Incorrect character in integer");
		return (2);
	}
	*fov = (double)var_int * M_PI / 180.0;
	return (0);
}

int	ft_parse_color_value(char *input, int line, double *color)
{
	int	var_int;
	int	err_code;

	err_code = ft_parse_integer(input, &var_int, 0, 255);
	if (err_code == 1)
	{
		ft_err_field(line, "Color", "Out of range [0, 255]");
		return (2);
	}
	else if (err_code == 2)
	{
		ft_err_field(line, "Color", "Incorrect character in integer");
		return (2);
	}
	*color = (double)var_int / 255.0;
	return (0);
}
