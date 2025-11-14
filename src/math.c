/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:43:29 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/14 01:13:49 by jose-jim         ###   ########.fr       */
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

t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z});
}

int	ft_solve_quadratic(double a, double b, double c, double *t0, double *t1)
{
	double	discriminant;
	double	q;
	double	temp;

	discriminant = b * b - 4 * a * c;
	if (ft_is_less(discriminant, 0.0))
		return (0);
	if (ft_is_greater(b, 0.0))
		q = -0.5 * (b + sqrt(discriminant));
	else
		q = -0.5 * (b - sqrt(discriminant));
	*t0 = q / a;
	*t1 = c / q;
	if (ft_is_greater(*t0, *t1))
	{
		temp = *t0;
		*t0 = *t1;
		*t1 = temp;
	}
	return (1);
}
