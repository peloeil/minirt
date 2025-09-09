/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_api.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:11:51 by rogiso            #+#    #+#             */
/*   Updated: 2025/09/08 17:11:51 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_API_H
# define MLX_API_H

# include <stdint.h>
# include <minirt/scene.h>
# define WINDOW_SCALE 0.8
# define ESC_KEY 65307

typedef struct s_image
{
	void	*img_ptr;
	uint8_t	*pixel_head;
	int		bits_per_pixel;
	int		bytes_per_pixel;
	int		bytes_per_line;
	int		endian;
}	t_image;

typedef struct s_display
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	image;
	int		x_len;
	int		y_len;
}	t_display;

typedef struct s_pixel
{
	int		x;
	int		y;
	t_color	color;
}	t_pixel;

// lifecycle.c
t_display	create_minirt_display(void);
void		destroy_minirt_display(const t_display display);

// img_pixel.c
void	enable_event_handler(const t_display *const display);
int		key_event_handler(const int key_code, const void *param);
int		close_button_handler(const void *param);

#endif
