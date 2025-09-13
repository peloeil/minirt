/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:13:03 by rogiso            #+#    #+#             */
/*   Updated: 2025/09/08 23:13:03 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include <X11/X.h>
#include <minirt/mlx_api.h>

void	enable_event_handler(const t_display *const display)
{
	mlx_hook(\
		display->win_ptr, \
		KeyPress, \
		KeyPressMask, \
		key_event_handler, \
		(void *)display \
	);
	mlx_hook(display->win_ptr, \
		DestroyNotify, \
		StructureNotifyMask, \
		close_button_handler, \
		(void *)display \
	);
}

int	key_event_handler(const int key_code, const void *param)
{
	const t_display	display = *(t_display *)param;

	if (key_code == ESC_KEY)
		mlx_loop_end(display.mlx_ptr);
	return (0);
}

int	close_button_handler(const void *param)
{
	const t_display	display = *(t_display *)param;

	mlx_loop_end(display.mlx_ptr);
	return (0);
}
