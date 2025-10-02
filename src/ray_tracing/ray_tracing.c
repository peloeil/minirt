/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:50:18 by rogiso            #+#    #+#             */
/*   Updated: 2025/09/04 18:50:18 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <libft/ft_string.h>
#include <minirt/scene.h>
#include <minirt/ray_tracing.h>

static t_ray	generate_ray_to_object(
					const t_line line,
					const void *const content,
					const bool ignore_light_source);
static t_ray	select_nearest_ray_intersection(
					const t_ray nearest_ray,
					const t_ray new_ray);

t_ray	find_nearest_ray_intersection(
			const t_line line,
			const t_scene *const scene,
			const bool ignore_light_source)
{
	t_ray			new_ray;
	t_ray			nearest_ray;
	const t_scene	*node = scene;

	ft_bzero(&nearest_ray, sizeof(nearest_ray));
	while (true)
	{
		new_ray = generate_ray_to_object(\
			line, node->content, ignore_light_source \
		);
		nearest_ray = select_nearest_ray_intersection(nearest_ray, new_ray);
		node = node->next;
		if (scene == node)
			break ;
	}
	return (nearest_ray);
}

static t_ray	generate_ray_to_object(
					const t_line line,
					const void *const content,
					const bool ignore_light_source)
{
	t_ray		ray;
	const t_tag	tag = *(t_tag *)content;

	ft_bzero(&ray, sizeof(ray));
	if (tag == SPHERE)
		ray = find_sphere_ray_intersection(\
			line, *(const t_sphere *)content \
		);
	else if (tag == PLANE)
		ray = find_plane_ray_intersection(\
			line, *(const t_plane *)content \
		);
	else if (tag == CYLINDER)
		ray = find_cylinder_ray_intersection(\
			line, *(const t_cylinder *)content \
		);
	else if (tag == LIGHT_SOURCE && !ignore_light_source)
	{
		ray = find_sphere_ray_intersection(\
			line, (*(const t_light_source *)content).sphere \
		);
		if (ray.hit_object == SPHERE)
			ray.hit_object = LIGHT_SOURCE;
	}
	return (ray);
}

static t_ray	select_nearest_ray_intersection(
					const t_ray nearest_ray,
					const t_ray new_ray)
{
	if (new_ray.hit_object == NONE)
		return (nearest_ray);
	if (nearest_ray.hit_object == NONE)
		return (new_ray);
	if (new_ray.line_t_coef < nearest_ray.line_t_coef)
		return (new_ray);
	return (nearest_ray);
}
