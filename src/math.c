/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:43:29 by jescuder          #+#    #+#             */
/*   Updated: 2026/02/02 18:53:10 by jescuder         ###   ########.fr       */
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
	if (d < 0.0)
		return (0);
	s = sqrt(d);
	t0 = (-b - s) / (2 * a);
	t1 = (-b + s) / (2 * a);
	if (t0 > t1)
	{
		s = t0;
		t0 = t1;
		t1 = s;
	}
	if (!ft_is_greater(t0, 0.0))
		t0 = t1;
	if (!ft_is_greater(t0, 0.0))
		return (0);
	*t = t0;
	return (1);
}
