/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:21:53 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/04 19:21:55 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	validate_rt_file_path(const char file_path[static 1])
{
	const int			fd = open(file_path, O_RDONLY);
	const size_t		len = ft_strlen(file_path);
	const char *const	ext = file_path - 3 + len;

	if (fd == -1)
		exit_with_message("rt file: failed to open rt file");
	close(fd);
	if (len < 3 || ft_strcmp(ext, ".rt") != 0)
		exit_with_message("rt file: file extension must be \".rt\"");
}

int	main(const int argc, const char *const argv[static argc])
{
	t_scene		*scene;
	t_camera	*camera;
	t_display	display;

	if (argc != 2)
		return (EXIT_FAILURE);
	validate_rt_file_path(argv[1]);
	scene = parse_rt_file(argv[1]);
	camera = find_camera(scene);
	display = create_minirt_display(camera);
	enable_event_handler(&display);
	render_scene(scene, camera, &display);
	mlx_loop(display.mlx_ptr);
	destroy_minirt_display(display);
	ft_list_clear(&scene, free);
	return (EXIT_SUCCESS);
}
