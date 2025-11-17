/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:43:29 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/18 00:14:48 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	ft_clamp(double value)
{
	if (value < 0.0)
		return (0.0);
	if (value > 1.0)
		return (1.0);
	return (value);
}

int	ft_solve_quadratic(double a, double b, double c, double *t)
{
	double	d;
	double	s;
	double	t0;
	double	t1;

	d = b * b - 4 * a * c;
	if (ft_is_less(d, 0.0))
		return (0);
	s = sqrt(d);
	t0 = (-b - s) / (2 * a);
	t1 = (-b + s) / (2 * a);
	if (ft_is_greater(t0, t1))
	{
		s = t0;
		t0 = t1;
		t1 = s;
	}
	if (ft_is_less(t0, 0.0))
		t0 = t1;
	if (ft_is_less(t0, 0.0))
		return (0);
	*t = t0;
	return (1);
}
