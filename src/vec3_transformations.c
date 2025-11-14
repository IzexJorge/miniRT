/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_transformations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:40:03 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/14 09:40:57 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec3_normalize(t_vec3 v)
{
	double	len;

	len = vec3_length(v);
	if (ft_is_equal(len, 0.0))
		return ((t_vec3){0.0, 0.0, 0.0});
	return (vec3_divide(v, len));
}

t_vec3	vec3_scale(t_vec3 v, double s)
{
	return ((t_vec3){v.x * s, v.y * s, v.z * s});
}

t_vec3	vec3_divide(t_vec3 v, double s)
{
	return ((t_vec3){v.x / s, v.y / s, v.z / s});
}
