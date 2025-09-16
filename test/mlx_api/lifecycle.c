#include <minirt/parser.h>
#include <minirt/scene.h>
#include <minirt/mlx_api.h>
#include <minirt/renderer.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <libft/ft_string.h>
#include <libft/ft_list.h>

void test_put_color_to_image_pixel(const t_display *const display)
{
	t_pixel pixel;

	pixel.y = 0;
	pixel.color = (t_color){255, 0, 0};
	while (pixel.y < display->y_len)
	{
		pixel.x = 0;
		while (pixel.x < display->x_len)
		{
			put_color_to_image_pixel(display, pixel);
			pixel.x++;
		}
		pixel.y++;
	}
	mlx_put_image_to_window(display->mlx_ptr, display->win_ptr, display->image.img_ptr, 0, 0);
}

int	main(void)
{
	t_scene		*scene;
	t_display	display;
	const char *path = "./scene_file/valid/example1.rt";

	scene = parse_rt_file(path);
	display = create_minirt_display(find_camera(scene));
	enable_event_handler(&display);
	test_put_color_to_image_pixel(&display);
	mlx_loop(display.mlx_ptr);
	destroy_minirt_display(display);
	ft_list_clear(&scene, free);
	return (EXIT_SUCCESS);
}
