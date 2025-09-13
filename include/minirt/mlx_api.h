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
	int		x_len;
	int		y_len;
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	image;
	t_vec3	to_virtual_display;
}	t_display;

typedef struct s_pixel
{
	int		x;
	int		y;
	t_color	color;
}	t_pixel;

// lifecycle.c
t_display	create_minirt_display(const t_camera *const camera);
void		destroy_minirt_display(const t_display display);

// event.c
void		enable_event_handler(const t_display *const display);
int			key_event_handler(const int key_code, const void *param);
int			close_button_handler(const void *param);

// img_pixel.c
void		put_color_to_image_pixel(
				const t_display *const display,
				t_pixel pixel);

#endif
