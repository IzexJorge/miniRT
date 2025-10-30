/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_oper2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 23:42:01 by jose-jim          #+#    #+#             */
/*   Updated: 2025/10/31 00:37:27 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec3_new(float x, float y, float z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

void	vec3_print(t_vec3 v)
{
	printf("vec3(%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
}

float	vec3_length(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	float	len;

	len = vec3_length(v);
	if (len == 0.0f)
		return ((t_vec3){0.0f, 0.0f, 0.0f});
	return (vec3_divide(v, len));
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	});
}
