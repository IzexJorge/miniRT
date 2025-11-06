
#include "miniRT.h"

static void	ft_debug_plane(void *plane_void)
{
	t_plane	*plane = plane_void;
	t_coord	coord = plane->coord;
	t_coord	orient = plane->orientation;
	t_color	color = plane->color;
	printf("Plane: %g,%g,%g  %g,%g,%g  %d,%d,%d\n", coord.x, coord.y, coord.z, orient.x, orient.y, orient.z, color.r, color.g, color.b);
}

static void	ft_debug_sphere(void *sphere_void)
{
	t_sphere	*sphere = sphere_void;
	t_coord		coord = sphere->coord;
	double		diameter = sphere->diameter;
	t_color		color = sphere->color;
	printf("Sphere: %g,%g,%g  %g  %d,%d,%d\n", coord.x, coord.y, coord.z, diameter, color.r, color.g, color.b);
}

static void	ft_debug_cylinder(void *cylinder_void)
{
	t_cylinder	*cylinder = cylinder_void;
	t_coord		coord = cylinder->coord;
	t_coord		orient = cylinder->orientation;
	double		diameter = cylinder->diameter;
	double		height = cylinder->height;
	t_color		color = cylinder->color;
	printf("Cylinder: %g,%g,%g  %g,%g,%g  %g  %g  %d,%d,%d\n", coord.x, coord.y, coord.z, orient.x, orient.y, orient.z, diameter, height, color.r, color.g, color.b);
}

//TODO QUITAR
void	ft_debug(t_scene *scene)
{
	printf("Escena correcta.\n");
	t_camera	*camera = scene->camera;
	t_coord		coord = camera->coord;
	t_coord		orient = camera->orientation;
	int			fov = camera->field_of_view;
	printf("Camera: %g,%g,%g  %g,%g,%g  %d\n", coord.x, coord.y, coord.z, orient.x, orient.y, orient.z, fov);

	t_ambient	*ambient = scene->ambient;
	double		ratio = ambient->ratio;
	t_color		color = ambient->color;
	printf("Ambient: %g  %d,%d,%d\n", ratio, color.r, color.g, color.b);

	t_light		*light = scene->light;
	coord = light->coord;
	ratio = light->ratio;
	printf("Light: %g,%g,%g %g\n", coord.x, coord.y, coord.z, ratio);

	ft_lstiter(scene->planes, ft_debug_plane);

	ft_lstiter(scene->spheres, ft_debug_sphere);

	ft_lstiter(scene->cylinders, ft_debug_cylinder);
}
