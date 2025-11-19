/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epsilon1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:06:33 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/19 15:44:44 by jose-jim         ###   ########.fr       */
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
