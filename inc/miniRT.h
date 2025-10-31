/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:02:26 by jescuder          #+#    #+#             */
/*   Updated: 2025/10/31 21:01:44 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
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
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct	s_camera
{
	t_coord	coord;
	t_coord	orientation;
	int		field_of_view;
}				t_camera;

typedef struct	s_ambient
{
	float	ratio;
	t_color	color;
}				t_ambient;

typedef struct	s_light
{
	t_coord	coord;
	float	ratio;
}				t_light;

typedef struct	s_plane
{
	t_coord	coord;
	t_coord	orientation;
	t_color	color;
}				t_plane;

typedef struct	s_sphere
{
	t_coord	coord;
	float	diameter;
	t_color	color;
}				t_sphere;

typedef struct	s_cylinder
{
	t_coord	coord;
	t_coord	orientation;
	float	diameter;
	float	height;
	t_color	color;
}				t_cylinder;

typedef struct	s_scene
{
	t_camera	*camera;
	t_ambient	*ambient;
	t_light		*light;
	t_list		*planes;
	t_list		*spheres;
	t_list		*cylinders;
}				t_scene;

typedef struct	s_mlx_data
{
	void	*mlx_ptr;
	void	*img_ptr;
	void	*win_ptr;
}				t_mlx_data;



int		main(int argc, char *argv[]);
int		ft_parse_scene(char *filename, t_scene *scene);
int		ft_render_image(t_scene *scene, void *img_ptr);
int		ft_show_image(void *mlx_ptr, void *img_ptr);

/* -------◊	VECTORS	◊------- */
typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

t_vec3	vec3_new(float x, float y, float z);
void	vec3_print(t_vec3 v);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, float s);
t_vec3	vec3_divide(t_vec3 v, float s);
float	vec3_dot(t_vec3 a, t_vec3 b);
float	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

#endif
