/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:56:00 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/26 20:56:00 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt/vec3.h>
#include <minirt/scene.h>
#include <minirt/ray_tracing.h>

static t_color	calculate_ambient_reflection(
					const t_color ray_color,
					const t_ambient_light amb_light);
static t_color	calculate_diffuse_reflection(
					const t_ray ray,
					const t_vec3 to_light,
					const t_light_source light_source);
static t_color	calculate_specular_reflection(
					const t_ray ray,
					const t_vec3 to_light,
					const t_light_source light_source,
					const double smoothness);
static t_color	calculate_intensity(
					const t_color light_color,
					const double brightness);

t_color	calculate_phong_reflection(
			const t_ray ray,
			const t_ambient_light amb_light,
			const t_light_source light_source)
{
	const t_vec3	to_light = \
		vec3_norm(vec3_sub(light_source.position, ray.intersection));
	const t_color	i_ambient = \
		calculate_ambient_reflection(ray.color, amb_light);
	const t_color	i_diffuse = \
		calculate_diffuse_reflection(ray, to_light, light_source);
	const t_color	i_specular = \
		calculate_specular_reflection(ray, to_light, light_source, 1);

	return ((t_color){
		fmin(i_ambient.red + i_diffuse.red + i_specular.red, 255),
		fmin(i_ambient.green + i_diffuse.green + i_specular.green, 255),
		fmin(i_ambient.blue + i_diffuse.blue + i_specular.blue, 255)
	});
}

static t_color	calculate_ambient_reflection(
					const t_color ray_color,
					const t_ambient_light amb_light)
{
	const t_color	intensity = \
		calculate_intensity(amb_light.color, amb_light.brightness);

	return ((t_color){
		ray_color.red * intensity.red,
		ray_color.green * intensity.green,
		ray_color.blue * intensity.blue
	});
}

static t_color	calculate_diffuse_reflection(
					const t_ray ray,
					const t_vec3 to_light,
					const t_light_source light_source)
{
	const t_color	intensity = \
		calculate_intensity(light_source.color, light_source.brightness);
	const double	n_dot_l = fmax(0, vec3_dot_prod(ray.hit_normal, to_light));

	return ((t_color){
		ray.color.red * intensity.red * n_dot_l,
		ray.color.green * intensity.green * n_dot_l,
		ray.color.blue * intensity.blue * n_dot_l
	});
}

static t_color	calculate_specular_reflection(
					const t_ray ray,
					const t_vec3 to_light,
					const t_light_source light_source,
					const double smoothness)
{
	const t_color	intensity = \
		calculate_intensity(light_source.color, light_source.brightness);
	const double	n_dot_l = fmax(0, vec3_dot_prod(ray.hit_normal, to_light));
	const t_vec3	reflection = \
		vec3_sub(vec3_mult(2 * n_dot_l, ray.hit_normal), to_light);
	const double	r_dot_v = \
		fmax(0, vec3_dot_prod(reflection, vec3_mult(-1, ray.line.direction)));
	const double	powed_r_dot_v = pow(r_dot_v, smoothness);

	return ((t_color){
		ray.color.red * intensity.red * powed_r_dot_v,
		ray.color.green * intensity.green * powed_r_dot_v,
		ray.color.blue * intensity.blue * powed_r_dot_v
	});
}

static t_color	calculate_intensity(
					const t_color light_color,
					const double brightness)
{
	return ((t_color){
		fmin(light_color.red * brightness, 255) / 255,
		fmin(light_color.green * brightness, 255) / 255,
		fmin(light_color.blue * brightness, 255) / 255
	});
}
