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
					const t_color object_color,
					const t_ambient_light amb_light);
static t_color	calculate_diffuse_reflection(
					const t_ray ray,
					const t_light_source light_source);
static t_color	calculate_specular_reflection(
					const t_ray ray,
					const t_light_source light_source,
					const double smoothness);

t_color	calculate_phong_reflection(
			const t_ray ray,
			const t_ambient_light amb_light,
			const t_light_source light_source)
{
	const t_color	i_ambient = \
		calculate_ambient_reflection(ray.object_color, amb_light);
	const t_color	i_diffuse = \
		calculate_diffuse_reflection(ray, light_source);
	const t_color	i_specular = \
		calculate_specular_reflection(ray, light_source, 1);

	return ((t_color){
		(int)fmin(i_ambient.R + i_diffuse.R + i_specular.R, 255),
		(int)fmin(i_ambient.G + i_diffuse.G + i_specular.G, 255),
		(int)fmin(i_ambient.B + i_diffuse.B + i_specular.B, 255)
	});
}

static t_color	calculate_ambient_reflection(
					const t_color object_color,
					const t_ambient_light amb_light)
{
	const t_color	intensity = (t_color){
		amb_light.color.R * amb_light.brightness,
		amb_light.color.G * amb_light.brightness,
		amb_light.color.B * amb_light.brightness \
	};

	return ((t_color){
		object_color.R * intensity.R / 255,
		object_color.G * intensity.G / 255,
		object_color.B * intensity.B / 255
	});
}

static t_color	calculate_diffuse_reflection(
					const t_ray ray,
					const t_light_source light_source)
{
	const t_color	intensity = (t_color){
		light_source.color.R * light_source.brightness,
		light_source.color.G * light_source.brightness,
		light_source.color.B * light_source.brightness \
	};
	const t_vec3	to_light = \
		vec3_norm(vec3_sub(light_source.position, ray.intersection));
	const double	n_dot_l = fmax(0, vec3_dot_prod(ray.normal, to_light));

	return ((t_color){
		ray.object_color.R * (intensity.R * n_dot_l) / 255,
		ray.object_color.G * (intensity.G * n_dot_l) / 255,
		ray.object_color.B * (intensity.B * n_dot_l) / 255
	});
}

static t_color	calculate_specular_reflection(
					const t_ray ray,
					const t_light_source light_source,
					const double smoothness)
{
	const t_color	intensity = (t_color){
		light_source.color.R * light_source.brightness,
		light_source.color.G * light_source.brightness,
		light_source.color.B * light_source.brightness \
	};
	const t_vec3	to_light = \
		vec3_norm(vec3_sub(light_source.position, ray.intersection));
	const double	n_dot_l = fmax(0, vec3_dot_prod(ray.normal, to_light));
	const t_vec3	reflection = \
		vec3_norm(vec3_sub(vec3_mult(2 * n_dot_l, ray.normal), to_light));
	const double	r_dot_v = \
		fmax(0, vec3_dot_prod(reflection, vec3_mult(-1, ray.line.direction)));

	return ((t_color){
		ray.object_color.R * intensity.R * pow(r_dot_v, smoothness) / 255,
		ray.object_color.G * intensity.G * pow(r_dot_v, smoothness) / 255,
		ray.object_color.B * intensity.B * pow(r_dot_v, smoothness) / 255
	});
}
