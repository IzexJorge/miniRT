/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:02:26 by jescuder          #+#    #+#             */
/*   Updated: 2025/10/29 15:28:15 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>

typedef struct	s_coord
{
	float x;
	float y;
	float z;
}				t_coord;

typedef struct	s_color
{
	float r;
	float g;
	float b;
}				t_color;

typedef struct	s_camera
{
	t_coord	coord;
	t_coord	orientation;
	int		field_of_view;//TODO Asegurarse de si tiene que ser entero o decimal.
}				t_camera;

typedef struct	s_ambient
{
	float	ratio;
	t_color	color;
}				t_ambient;

typedef struct	s_light
{
	float	ratio;
	t_coord	coord;
}				t_light;

typedef struct	s_plane
{
	t_coord	coord;
	t_color	color;
	t_coord	orientation;
}				t_plane;

typedef struct	s_sphere
{
	t_coord	coord;
	t_color	color;
	float	diameter;
}				t_sphere;

typedef struct	s_cylinder
{
	t_coord	coord;
	t_color	color;
	float	diameter;
	float	height;
	t_coord	orientation;
}				t_cylinder;

typedef struct	s_scene
{
	t_camera	*camera;
	t_ambient	*ambient;
	t_light		*light;
	t_plane		*planes;
	t_sphere	*spheres;
	t_cylinder	*cylinders;
}				t_scene;

int	main(int argc, char *argv[]);
int	ft_parse_scene(char *filename, t_scene *scene);

#endif
