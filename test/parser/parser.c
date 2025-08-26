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
    "LINE",
    "PLANE",
    "SPHERE",
    "CYLINDER",
    "CAMERA",
    "AMBIENT_LIGHT",
    "LIGHT_SOURCE"
};

static void print_vecter_obj(const char str[static 1], const t_vec3 vec)
{
    printf("%-24s: {%f, %f, %f}\n", str, vec.x, vec.y, vec.z);
}

static void print_ambient_light_info(const t_ambient_light ambient_light)
{
    printf("[t_ambient_light]\n");
    printf("%-24s: %s\n", "ambient_light.tag", tag_str[ambient_light.tag]);
    printf("%-24s: %f\n", "ambient_light.brightness", ambient_light.brightness);
    printf("%-24s: %x\n\n", "ambient_light.color", ambient_light.color);
}

static void print_camera_info(const t_camera camera)
{
    printf("[t_camera]\n");
    printf("%-24s: %s\n", "camera.tag", tag_str[camera.tag]);
    print_vecter_obj("camera.position", camera.position);
    print_vecter_obj("camera.direction", camera.direction);
    printf("%-24s: %f\n\n", "camera.radian", camera.radian);
}

static void print_light_source_info(const t_light_source light_source)
{
    printf("[t_light_source]\n");
    printf("%-24s: %s\n", "light_source.tag", tag_str[light_source.tag]);
    print_vecter_obj("light_source.position", light_source.position);
    printf("%-24s: %f\n", "light_source.brightness", light_source.brightness);
    printf("%-24s: %x\n\n", "light_source.color", light_source.color);
}

static void print_sphere_info(const t_sphere sphere)
{
    printf("[t_sphere]\n");
    printf("%-24s: %s\n", "sphere.tag", tag_str[sphere.tag]);
    printf("%-24s: %f\n", "sphere.radius", sphere.radius);
    print_vecter_obj("sphere.center", sphere.center);
    printf("%-24s: %x\n\n", "sphere.color", sphere.color);
}

static void print_plane_info(const t_plane plane)
{
    printf("[t_plane]\n");
    printf("%-24s: %s\n", "plane.tag", tag_str[plane.tag]);
    print_vecter_obj("plane.position", plane.position);
    print_vecter_obj("plane.normal", plane.normal);
    printf("%-24s: %x\n\n", "plane.color", plane.color);
}

static void print_cylinder_info(const t_cylinder cylinder)
{
    printf("[t_cylinder]\n");
    printf("%-24s: %s\n", "cylinder.tag", tag_str[cylinder.tag]);
    print_vecter_obj("cylinder.center", cylinder.center);
    print_vecter_obj("cylinder.axis", cylinder.axis);
    printf("%-24s: %f\n", "cylinder.radius", cylinder.radius);
    printf("%-24s: %f\n", "cylinder.height", cylinder.height);
    printf("%-24s: %x\n\n", "cylinder.color", cylinder.color);
}

static void print_scene_list(const t_scene *scene)
{
    t_tag tag;
    const t_scene *current;

    current = scene;
    while (true)
    {
        tag = *(t_tag *)current->content;
        if (tag == AMBIENT_LIGHT)
            print_ambient_light_info(*(t_ambient_light *)current->content);
        if (tag == CAMERA)
            print_camera_info(*(t_camera *)current->content);
        if (tag == LIGHT_SOURCE)
            print_light_source_info(*(t_light_source *)current->content);
        if (tag == SPHERE)
            print_sphere_info(*(t_sphere *)current->content);
        if (tag == PLANE)
            print_plane_info(*(t_plane *)current->content);
        if (tag == CYLINDER)
            print_cylinder_info(*(t_cylinder *)current->content);
        current = current->next;
        if (scene == current)
            break ;
    }
}

// void test_parse_rt_files(const char path[])
// {
//     t_scene *scene;
//     char *num_str;
//     char *rt_file;

//     for (int i = 1; i < INT_MAX; i++)
//     {
//         num_str = atoi(i);
//         rt_file = ft_strjoin(path, num_str);
//         if (access(rt_file, F_OK))
//         {
//             validate_rt_file_path();
//             scene = parse_rt_file();
//             print_scene_list(scene);
//             ft_list_clear(&scene, free);
//         }
//         free(num_str);
//         free(rt_file);
//     }
// }

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
    print_scene_list(scene);
    ft_list_clear(&scene, free);
    return (EXIT_SUCCESS);
}
