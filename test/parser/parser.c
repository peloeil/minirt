#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include <libft/ft_string.h>
#include <minirt/vec3.h>
#include <minirt/scene.h>
#include <minirt/parser.h>

static const char *const tag_str[] = {
    "NONE",
    "LINE",
    "PLANE",
    "SPHERE",
    "CYLINDER",
    "CAMERA",
    "AMBIENT_LIGHT",
    "LIGHT_SOURCE"
};

static void print_vector_obj(const char str[static 1], const t_vec3 vec)
{
    printf("%-24s: {%f, %f, %f}\n", str, vec.x, vec.y, vec.z);
}

static void print_color_obj(const char str[static 1], const t_color color, bool is_end_line)
{
    if (is_end_line)
        printf("%-24s: RGB = (%.1f, %.1f, %.1f)\n\n", str, color.red, color.green, color.blue);
    else
        printf("%-24s: RGB = (%.1f, %.1f, %.1f)\n", str, color.red, color.green, color.blue);
}

static void print_ambient_light_info(const t_ambient_light ambient_light)
{
    printf("[t_ambient_light]\n");
    printf("%-24s: %s\n", "ambient_light.tag", tag_str[ambient_light.tag]);
    printf("%-24s: %f\n", "ambient_light.brightness", ambient_light.brightness);
    print_color_obj("ambient_light.color", ambient_light.color, true);
}

static void print_camera_info(const t_camera camera)
{
    printf("[t_camera]\n");
    printf("%-24s: %s\n", "camera.tag", tag_str[camera.tag]);
    print_vector_obj("camera.position", camera.position);
    print_vector_obj("camera.forward", camera.forward);
    printf("%-24s: %f\n\n", "camera.radian", camera.radian);
}

static void print_light_source_info(const t_light_source light_source)
{
    printf("[t_light_source]\n");
    printf("%-24s: %s\n", "light_source.tag", tag_str[light_source.tag]);
    print_vector_obj("light_source.position", light_source.position);
    printf("%-24s: %f\n", "light_source.brightness", light_source.brightness);
    print_color_obj("light_source.color", light_source.color, true);
}

static void print_sphere_info(const t_sphere sphere)
{
    printf("[t_sphere]\n");
    printf("%-24s: %s\n", "sphere.tag", tag_str[sphere.tag]);
    print_vector_obj("sphere.center", sphere.center);
    printf("%-24s: %f\n", "sphere.radius", sphere.radius);
    print_color_obj("sphere.color", sphere.color, true);
}

static void print_plane_info(const t_plane plane)
{
    printf("[t_plane]\n");
    printf("%-24s: %s\n", "plane.tag", tag_str[plane.tag]);
    print_vector_obj("plane.position", plane.position);
    print_vector_obj("plane.normal", plane.normal);
    print_color_obj("plane.color", plane.color, true);
}

static void print_cylinder_info(const t_cylinder cylinder)
{
    printf("[t_cylinder]\n");
    printf("%-24s: %s\n", "cylinder.tag", tag_str[cylinder.tag]);
    print_vector_obj("cylinder.center", cylinder.center);
    print_vector_obj("cylinder.axis", cylinder.axis);
    printf("%-24s: %f\n", "cylinder.radius", cylinder.radius);
    printf("%-24s: %f\n", "cylinder.height", cylinder.height);
    print_color_obj("cylinder.color", cylinder.color, true);
}

static void print_scene_list(const t_scene *scene)
{
    t_tag tag;
    const t_scene *node = scene;

    while (true)
    {
        if (!node)
            exit(EXIT_FAILURE);
        tag = *(t_tag *)node->content;
        if (tag == AMBIENT_LIGHT)
            print_ambient_light_info(*(t_ambient_light *)node->content);
        if (tag == CAMERA)
            print_camera_info(*(t_camera *)node->content);
        if (tag == LIGHT_SOURCE)
            print_light_source_info(*(t_light_source *)node->content);
        if (tag == SPHERE)
            print_sphere_info(*(t_sphere *)node->content);
        if (tag == PLANE)
            print_plane_info(*(t_plane *)node->content);
        if (tag == CYLINDER)
            print_cylinder_info(*(t_cylinder *)node->content);
        node = node->next;
        if (scene == node)
            break ;
    }
}

static void	validate_rt_file_path(const char file_path[static 1])
{
	const int			fd = open(file_path, O_RDONLY);
	const size_t		len = ft_strlen(file_path);
	const char *const	ext = file_path - 3 + len;

	if (fd == -1)
		exit(EXIT_FAILURE);
	close(fd);
	if (len < 3 || ft_strcmp(ext, ".rt") != 0)
		exit(EXIT_FAILURE);
}

int main(int argc, char *argv[static 2])
{
    t_scene *scene;

	if (argc != 2)
		return (EXIT_FAILURE);
    validate_rt_file_path(argv[1]);
    scene = parse_rt_file(argv[1]);
    if (!scene)
        exit(EXIT_FAILURE);
    print_scene_list(scene);
    ft_list_clear(&scene, free);
    return (EXIT_SUCCESS);
}
