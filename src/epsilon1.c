/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epsilon1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:06:33 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/07 20:47:56 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_is_equal(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}

int	ft_is_greater(double a, double b)
{
	return (a > b + EPSILON);
}

int	ft_is_less(double a, double b)
{
	return (a < b - EPSILON);
}

int	ft_is_greater_equal(double a, double b)
{
	return (a > b - EPSILON);
}

int	ft_is_less_equal(double a, double b)
{
	return (a < b + EPSILON);
}