/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:02:26 by jescuder          #+#    #+#             */
/*   Updated: 2025/11/14 23:24:58 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <float.h>
# include <errno.h>
# include <stdint.h>
# include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define EPSILON 1e-8
# define WIN_WIDTH 500
# define WIN_HEIGHT 500

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

typedef t_vec3	t_color;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}			t_ray;

typedef struct s_hit
{
	char	type;
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
	double	t;
}			t_hit;

typedef struct s_camera
{
	t_vec3	coord;
	t_vec3	orient;
	double	fov;
	double	fov_rad;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	w_p;
	double	focal_len;
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
	t_vec3	orient;
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
	t_vec3	orient;
	double	diameter;
	double	height;
	t_color	color;
	t_vec3	normal;
}			t_cylinder;

typedef struct s_scene
{
	t_camera	*camera;
	t_ambient	*ambient;
	t_light		*light;
	t_list		*planes;
	t_list		*spheres;
	t_list		*cylinders;
	int			num_planes;
	int			num_spheres;
	int			num_cylinders;
}				t_scene;

typedef struct s_image
{
	void	*inner;
	char	*data;
	int		bits_per_pixel;
	int		line_bytes;
	int		endian;
}			t_image;

typedef struct s_mlx_data
{
	void	*mlx;
	t_image	*img;
	void	*win;
}			t_mlx_data;

int		main(int argc, char *argv[]);
int		ft_show_image(void *mlx, t_image *img);

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
int		ft_parse_orient(char *input, int line, t_vec3 *orient);

int		ft_parse_field_of_view(char *input, int line, double *fov);
int		ft_parse_color_value(char *input, int line, double *color);
int		ft_parse_decimal(char *input, int line, char *field, double *var);

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
double	vec3_length(t_vec3 v);

t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_scale(t_vec3 v, double s);
t_vec3	vec3_divide(t_vec3 v, double s);

t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_mul(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_dot(t_vec3 a, t_vec3 b);

/* -------◊	MATH	◊------- */
double	ft_clamp(double value);
t_vec3	vec3_mul(t_vec3 a, t_vec3 b);
int		ft_solve_quadratic(double a, double b, double c, double *t0, double *t1);

/* -------◊	RENDER	◊------- */
void	ft_render_image(t_image *img, t_scene *scene);
t_color	ft_get_pixel_color(int x, int y, t_scene *scene);
t_color	ft_trace_ray(t_ray ray, t_scene *scene);
t_color	ft_shade(t_ray ray, t_scene *scene, t_hit *hit);

void	ft_init_camera(t_camera *cam);
t_vec3	ft_get_ray_direction(int x, int y, t_camera *cam);

/* -------◊	SPHERE	◊------- */
int		ft_intersect_sphere(t_ray ray, t_sphere *sp, double *t);
void	ft_search_spheres(t_ray ray, t_scene *scene, double *min_t, t_hitpoint *hit);

/* -------◊	PLANE	◊------- */
int		ft_intersect_plane(t_ray ray, t_plane *pl, double *t);
void	ft_search_planes(t_ray ray, t_scene *scene, double *min_t, t_hitpoint *hit);

/* -------◊	CYLINDER	◊------- */
int		ft_intersect_cylinder(t_ray ray, t_cylinder *cy, double *t);
void	ft_search_cyl(t_ray ray, t_scene *scene, double *min_t, t_hitpoint *hit);
void	ft_search_spheres(t_ray ray, t_scene *scene, double *min_t, t_hit *hit);

#endif
