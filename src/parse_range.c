/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:44:22 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/06 19:00:42 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_max_int(char *field)
{
	if (!ft_strcmp(field, "Color"))
		return (255);
	else
		return (180);
}

double	ft_min_dec(char *field)
{
	if (!ft_strcmp(field, "Ratio"))
		return (0.0);
	else if (!ft_strcmp(field, "Orientation"))
		return (-1.0);
	else
		return (-10000.0);
}

double	ft_max_dec(char *field)
{
	if (!ft_strcmp(field, "Ratio") || !ft_strcmp(field, "Orientation"))
		return (1.0);
	else
		return (10000.0);
}
