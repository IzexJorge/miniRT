/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:27:11 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/06 19:00:58 by jescuder         ###   ########.fr       */
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

static int	ft_internal(char *input, int *var, int min, int max)
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

int	ft_parse_integer(char *input, int line, char *field, int *var)
{
	int	err_code;

	err_code = ft_internal(input, var, 0, ft_max_int(field));
	if (err_code > 0)
	{
		if (err_code == 1)
		{
			if (!ft_strcmp(field, "Color"))
				ft_err_field(line, field, "Out of range [0, 255].");
			else
				ft_err_field(line, field, "Out of range [0, 180].");
		}
		else if (err_code == 2)
			ft_err_field(line, field, "Incorrect characters in integer.");
		return (2);
	}
	return (0);
}
