/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:44:16 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/07 16:41:23 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	ft_get_sign(char **input)
{
	double	sign;

	while (ft_isspace(**input))
		(*input)++;
	if (**input == '-')
	{
		sign = -1.0;
		(*input)++;
	}
	else
	{
		sign = 1.0;
		if (**input == '+')
			(*input)++;
	}
	return (sign);
}

static int	ft_get_int_part(char **input, double *var, double max)
{
	double	int_part;

	int_part = 0.0;
	while (ft_isdigit(**input))
	{
		int_part = int_part * 10.0 + (**input - '0');
		if (int_part > max)
			return (1);
		(*input)++;
	}
	*var = int_part;
	return (0);
}

static int	ft_get_frac_part(char **input, double *var)
{
	double	mantissa;
	double	divisor;
	double	frac_part;

	mantissa = 0.0;
	divisor = 1.0;
	while (ft_isdigit(**input))
	{
		if (divisor > DBL_MAX / 10.0)
			return (1);
		divisor *= 10.0;
		mantissa = mantissa * 10.0 + (**input - '0');
		(*input)++;
	}
	frac_part = mantissa / divisor;
	if (mantissa != 0.0 && (frac_part == 0.0 || ft_is_zero(frac_part)))
		return (1);
	*var = frac_part;
	return (0);
}

static int	ft_internal(char *input, double *var, double min, double max)
{
	double	sign;
	double	result;
	double	frac_part;

	sign = ft_get_sign(&input);
	if (ft_get_int_part(&input, &result, max))
		return (1);
	if (*input == '.')
	{
		input++;
		if (ft_get_frac_part(&input, &frac_part))
			return (2);
		result += frac_part;
		if (result > max)
			return (1);
	}
	if (*input != '\0')
		return (3);
	result *= sign;
	if (result < min)
		return (1);
	*var = result;
	return (0);
}

int	ft_parse_decimal(char *input, int line, char *field, double *var)
{
	int	err_code;

	err_code = ft_internal(input, var, ft_min_dec(field), ft_max_dec(field));
	if (err_code > 0)
	{
		if (err_code == 1)
		{
			if (!ft_strcmp(field, "Ratio"))
				ft_err_field(line, field, "Out of range [0.0, 1.0]");
			else if (!ft_strcmp(field, "Orientation"))
				ft_err_field(line, field, "Out of range [-1.0, 1.0]");
			else
				ft_err_field(line, field, "Out of range [-10000.0, 10000.0]");
		}
		else if (err_code == 2)
			ft_err_field(line, field, "Fractional part is smaller than 1e-8");
		else if (err_code == 3)
			ft_err_field(line, field, "Incorrect character in decimal");
		return (2);
	}
	return (0);
}
