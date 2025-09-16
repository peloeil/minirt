/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:36:26 by rogiso            #+#    #+#             */
/*   Updated: 2025/09/07 20:36:26 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <minirt/vec3.h>
#include <minirt/scene.h>
#include <minirt/mlx_api.h>

static t_vec3	calculate_camera_to_virtual_display(
					const int x_len,
					const t_camera *const camera);

t_display	create_minirt_display(const t_camera *const camera)
{
	t_display	display;

	display.mlx_ptr = mlx_init();
	if (!display.mlx_ptr)
		exit(EXIT_FAILURE);
	mlx_get_screen_size(display.mlx_ptr, &display.x_len, &display.y_len);
	display.x_len = (int)(display.x_len * WINDOW_SCALE);
	display.y_len = (int)(display.y_len * WINDOW_SCALE);
	display.win_ptr = mlx_new_window(\
		display.mlx_ptr, display.x_len, display.y_len, "miniRT" \
	);
	display.image.img_ptr = mlx_new_image(\
		display.mlx_ptr, display.x_len, display.y_len \
	);
	display.image.pixel_head = (uint8_t *)mlx_get_data_addr(\
		display.image.img_ptr, \
		&display.image.bits_per_pixel, \
		&display.image.bytes_per_line, \
		&display.image.endian \
	);
	display.image.bytes_per_pixel = display.image.bits_per_pixel / 8;
	display.to_virtual_display = calculate_camera_to_virtual_display(\
		display.x_len, camera \
	);
	return (display);
}

static t_vec3	calculate_camera_to_virtual_display(
					const int x_len,
					const t_camera *const camera)
{
	const double	distance_to_vir_display = (\
		(double)(x_len / 2.0) / tan(camera->radian / 2) \
	);

	return (vec3_mult(distance_to_vir_display, camera->forward));
}

void	destroy_minirt_display(const t_display display)
{
	mlx_destroy_image(display.mlx_ptr, display.image.img_ptr);
	mlx_destroy_window(display.mlx_ptr, display.win_ptr);
	mlx_destroy_display(display.mlx_ptr);
	free(display.mlx_ptr);
}
