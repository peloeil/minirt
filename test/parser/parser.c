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
    printf("%s{%f, %f, %f}\n", str, vec.x, vec.y, vec.z);
}

static void print_ambient_light_info(const t_ambient_light ambient_light)
{
    printf("[t_ambient_light]\n");
    printf("ambient_light.tag       : %s\n", tag_str[ambient_light.tag]);
    printf("ambient_light.brightness: %f\n", ambient_light.brightness);
    printf("ambient_light.color     : %x\n\n", ambient_light.color);
}

static void print_camera_info(const t_camera camera)
{
    printf("[t_camera]\n");
    printf("camera.tag      : %s\n", tag_str[camera.tag]);
    print_vecter_obj("camera.position : ", camera.position);
    print_vecter_obj("camera.direction: ", camera.direction);
    printf("camera.radian   : %f\n\n", camera.radian);
}

static void print_light_source_info(const t_light_source light_source)
{
    printf("[t_light_source]\n");
    printf("light_source.tag       : %s\n", tag_str[light_source.tag]);
    print_vecter_obj("light_source.position  : ", light_source.position);
    printf("light_source.brightness: %f\n", light_source.brightness);
    printf("light_source.color     : %x\n\n", light_source.color);
}

static void print_sphere_info(const t_sphere sphere)
{
    printf("[t_sphere]\n");
    printf("sphere.tag   : %s\n", tag_str[sphere.tag]);
    printf("sphere.radius: %f\n", sphere.radius);
    print_vecter_obj("sphere.center: ", sphere.center);
    printf("sphere.color : %x\n\n", sphere.color);
}

static void print_plane_info(const t_plane plane)
{
    printf("[t_plane]\n");
    printf("plane.tag     : %s\n", tag_str[plane.tag]);
    print_vecter_obj("plane.position: ", plane.position);
    print_vecter_obj("plane.normal  : ", plane.normal);
    printf("plane.color   : %x\n\n", plane.color);
}

static void print_cylinder_info(const t_cylinder cylinder)
{
    printf("[t_cylinder]\n");
    printf("cylinder.tag   : %s\n", tag_str[cylinder.tag]);
    print_vecter_obj("cylinder.center: ", cylinder.center);
    print_vecter_obj("cylinder.axis  : ", cylinder.axis);
    printf("cylinder.radius: %f\n", cylinder.radius);
    printf("cylinder.height: %f\n", cylinder.height);
    printf("cylinder.color : %x\n\n", cylinder.color);
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
            print_ambient_light_info(*(t_ambient_light *)scene->content);
        if (tag == CAMERA)
            print_camera_info(*(t_camera *)scene->content);
        if (tag == LIGHT_SOURCE)
            print_light_source_info(*(t_light_source *)scene->content);
        if (tag == SPHERE)
            print_sphere_info(*(t_sphere *)scene->content);
        if (tag == PLANE)
            print_plane_info(*(t_plane *)scene->content);
        if (tag == CYLINDER)
            print_cylinder_info(*(t_cylinder *)scene->content);
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
