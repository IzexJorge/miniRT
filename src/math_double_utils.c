/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:06:33 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/03 20:43:04 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_is_zero(double a)
{
	return (fabs(a) < FT_EPSILON);
}

int	ft_is_equal(double a, double b)
{
	return (fabs(a - b) < FT_EPSILON);
}
