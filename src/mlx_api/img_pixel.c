/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:58:54 by rogiso            #+#    #+#             */
/*   Updated: 2025/09/08 21:58:54 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <minirt/scene.h>
#include <minirt/mlx_api.h>
#include <minirt/renderer.h>

static uint32_t	convert_color_object(const t_color color);

void	put_color_to_image_pixel(const t_display *const display, t_pixel pixel)
{
	const int		x = display->x_len - pixel.x - 1;
	const int		y = display->y_len - pixel.y - 1;
	const uint32_t	color = convert_color_object(pixel.color);
	const uint8_t	*pixel_addr = (uint8_t *)(\
		display->image.pixel_head \
		+ x * (display->image.bits_per_pixel / 8) \
		+ y * display->image.bytes_per_line \
	);

	*(uint32_t *)pixel_addr = color;
}

static uint32_t	convert_color_object(const t_color color)
{
	return ((uint32_t)
		(
			(uint32_t)color.red << 16
			|| (uint32_t)color.green << 8
			|| (uint32_t)color.blue
		)
	);
}
