
#include "miniRT.h"

static void	ft_debug_plane(void *plane_void)
{
	t_plane	*plane = plane_void;
	t_vec3	coord = plane->coord;
	t_vec3	orient = plane->orient;
	t_color	color = plane->color;
	printf("Plane: %g,%g,%g  %g,%g,%g  %g,%g,%g\n", coord.x, coord.y, coord.z, orient.x, orient.y, orient.z, color.x, color.y, color.z);
}

static void	ft_debug_sphere(void *sphere_void)
{
	t_sphere	*sphere = sphere_void;
	t_vec3		coord = sphere->coord;
	double		diameter = sphere->diameter;
	t_color		color = sphere->color;
	printf("Sphere: %g,%g,%g  %g  %g,%g,%g\n", coord.x, coord.y, coord.z, diameter, color.x, color.y, color.z);
}

static void	ft_debug_cylinder(void *cylinder_void)
{
	t_cylinder	*cylinder = cylinder_void;
	t_vec3		coord = cylinder->coord;
	t_vec3		orient = cylinder->orient;
	double		diameter = cylinder->diameter;
	double		height = cylinder->height;
	t_color		color = cylinder->color;
	printf("Cylinder: %g,%g,%g  %g,%g,%g  %g  %g  %g,%g,%g\n", coord.x, coord.y, coord.z, orient.x, orient.y, orient.z, diameter, height, color.x, color.y, color.z);
}

//TODO QUITAR
void	ft_debug(t_scene *scene)
{
	printf("Escena correcta.\n");
	t_camera	*camera = scene->camera;
	t_vec3		coord = camera->coord;
	t_vec3		orient = camera->orient;
	double		fov = camera->fov;
	printf("Camera: %g,%g,%g  %g,%g,%g  %g\n", coord.x, coord.y, coord.z, orient.x, orient.y, orient.z, fov);

	t_ambient	*ambient = scene->ambient;
	double		ratio = ambient->ratio;
	t_color		color = ambient->color;
	printf("Ambient: %g  %g,%g,%g\n", ratio, color.x, color.y, color.z);

	t_light		*light = scene->light;
	coord = light->coord;
	ratio = light->ratio;
	printf("Light: %g,%g,%g %g\n", coord.x, coord.y, coord.z, ratio);

	printf("Planes: %d\n", scene->num_planes);
	ft_lstiter(scene->planes, ft_debug_plane);

	printf("Spheres: %d\n", scene->num_spheres);
	ft_lstiter(scene->spheres, ft_debug_sphere);

	printf("Cylinders: %d\n", scene->num_cylinders);
	ft_lstiter(scene->cylinders, ft_debug_cylinder);
}
