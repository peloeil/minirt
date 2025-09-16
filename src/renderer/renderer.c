/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 21:18:11 by rogiso            #+#    #+#             */
/*   Updated: 2025/09/09 21:18:11 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <minirt/vec3.h>
#include <minirt/scene.h>
#include <minirt/mlx_api.h>
#include <minirt/ray_tracing.h>
#include <minirt/renderer.h>

static t_ray	create_ray(
					const t_pixel pixel,
					const t_scene *const scene,
					const t_camera *const camera,
					const t_display *const display);
static t_line	create_ray_line(
					const t_pixel pixel,
					const t_camera *const camera,
					const t_display *const display);

void	render_scene(
			const t_scene *const scene,
			const t_camera *const camera,
			const t_display *const display)
{
	t_ray							ray;
	t_pixel							pixel;
	const t_light_source *const		light = find_light_source(scene);
	const t_ambient_light *const	amb_light = find_ambient_light(scene);

	pixel.y = 0;
	while (pixel.y < display->y_len)
	{
		pixel.x = 0;
		while (pixel.x < display->x_len)
		{
			ray = create_ray(pixel, scene, camera, display);
			pixel.color = calculate_phong_reflection(\
				ray, scene, *amb_light, *light \
			);
			put_color_to_image_pixel(display, pixel);
			pixel.x++;
		}
		pixel.y++;
	}
	mlx_put_image_to_window(\
		display->mlx_ptr, display->win_ptr, display->image.img_ptr, 0, 0 \
	);
}

static t_ray	create_ray(
					const t_pixel pixel,
					const t_scene *const scene,
					const t_camera *const camera,
					const t_display *const display)
{
	const t_line	ray_line = create_ray_line(pixel, camera, display);

	return (find_nearest_ray_intersection(ray_line, scene));
}

static t_line	create_ray_line(
					const t_pixel pixel,
					const t_camera *const camera,
					const t_display *const display)
{
	const t_vec3	to_right = vec3_mult(\
		(double)pixel.x - (double)(display->x_len / 2.0), camera->right \
	);
	const t_vec3	to_up = vec3_mult(\
		(double)pixel.y - (double)(display->y_len / 2.0), camera->up \
	);
	const t_vec3	target = vec3_add(\
		vec3_add(to_right, to_up), \
		display->to_virtual_display \
	);

	return ((t_line){
		LINE, camera->position, vec3_norm(target)
	});
}
