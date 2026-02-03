/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_range.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:44:22 by jescuder          #+#    #+#             */
/*   Updated: 2026/02/03 11:55:29 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	ft_min_dec(char *field)
{
	if (!ft_strcmp(field, "Orientation"))
		return (-1.0);
	else if (!ft_strcmp(field, "Coordinates"))
		return (-10000.0);
	else if (!ft_strcmp(field, "Height") || !ft_strcmp(field, "Diameter"))
		return (-2.0);
	else
		return (0.0);
}

double	ft_max_dec(char *field)
{
	if (!ft_strcmp(field, "Ratio") || !ft_strcmp(field, "Orientation"))
		return (1.0);
	else if (!ft_strcmp(field, "Color"))
		return (255.0);
	else if (!ft_strcmp(field, "FOV"))
		return (180.0);
	else
		return (10000.0);
}
