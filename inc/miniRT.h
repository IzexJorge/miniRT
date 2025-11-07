/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:02:26 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/07 20:47:54 by jescuder         ###   ########.fr       */
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
# include <float.h>

# define EPSILON 1e-8

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct s_camera
{
	t_vec3	coord;
	t_vec3	orientation;
	int		field_of_view;
}			t_camera;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}			t_ambient;

typedef struct s_light
{
	t_vec3	coord;
	double	ratio;
}			t_light;

typedef struct s_plane
{
	t_vec3	coord;
	t_vec3	orientation;
	t_color	color;
}			t_plane;

typedef struct s_sphere
{
	t_vec3	coord;
	double	diameter;
	t_color	color;
}			t_sphere;

typedef struct s_cylinder
{
	t_vec3	coord;
	t_vec3	orientation;
	double	diameter;
	double	height;
	t_color	color;
}			t_cylinder;

typedef struct s_scene
{
	t_camera	*camera;
	t_ambient	*ambient;
	t_light		*light;
	t_list		*planes;
	t_list		*spheres;
	t_list		*cylinders;
}				t_scene;

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*img_ptr;
	void	*win_ptr;
}			t_mlx_data;

int		main(int argc, char *argv[]);
int		ft_show_image(void *mlx_ptr, void *img_ptr);

/* -------◊	EPSILON	◊------- */
int		ft_is_equal(double a, double b);
int		ft_is_greater(double a, double b);
int		ft_is_less(double a, double b);
int		ft_is_greater_equal(double a, double b);
int		ft_is_less_equal(double a, double b);
int		ft_is_zero(double a);

/* -------◊	PARSE	◊------- */
int		ft_parse_scene(char *filename, t_scene *scene);

int		ft_parse_ambient(char **line_inputs, int line, t_scene *scene);
int		ft_parse_light(char **line_inputs, int line, t_scene *scene);
int		ft_parse_plane(char **line_inputs, int line, t_scene *scene);
int		ft_parse_sphere(char **line_inputs, int line, t_scene *scene);
int		ft_parse_cylinder(char **line_inputs, int line, t_scene *scene);

int		ft_parse_color(char *input, int line, t_color *color);
int		ft_parse_coord(char *input, int line, t_vec3 *coordinates);
int		ft_parse_orient(char *input, int line, t_vec3 *orientation);

int		ft_parse_integer(char *input, int line, char *field, int *var);
int		ft_parse_decimal(char *input, int line, char *field, double *var);

int		ft_max_int(char *field);
double	ft_min_dec(char *field);
double	ft_max_dec(char *field);

void	ft_err_line(int line, char *message);
void	ft_err_field(int line, char *field, char *message);
void	ft_err_free(char *message, int line, char **array);

//TODO QUITAR
void ft_debug(t_scene *scene);

/* -------◊	VECTORS	◊------- */
t_vec3	vec3_new(double x, double y, double z);
void	vec3_print(t_vec3 v);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double s);
t_vec3	vec3_divide(t_vec3 v, double s);
double	vec3_dot(t_vec3 a, t_vec3 b);
double	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

/* -------◊	RENDER	◊------- */
int		ft_render_image(t_scene *scene, void *img_ptr);

#endif
