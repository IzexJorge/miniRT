/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:26:37 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/03 20:43:07 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_is_greater(double a, double b)
{
	return (a > b + FT_EPSILON);
}

int	ft_is_less(double a, double b)
{
	return (a < b - FT_EPSILON);
}

int	ft_is_greater_equal(double a, double b)
{
	return (a > b - FT_EPSILON);
}

int	ft_is_less_equal(double a, double b)
{
	return (a < b + FT_EPSILON);
}
