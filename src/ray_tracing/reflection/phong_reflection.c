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
					const t_vec3 to_light,
					const t_light_source light_source);
static t_color	calculate_specular_reflection(
					const t_ray ray,
					const t_vec3 to_light,
					const t_light_source light_source,
					const double smoothness);

t_color	calculate_phong_reflection(
			const t_ray ray,
			const t_ambient_light amb_light,
			const t_light_source light_source)
{
	const t_vec3	to_light = \
		vec3_norm(vec3_sub(light_source.position, ray.intersection));
	const t_color	i_ambient = \
		calculate_ambient_reflection(ray.obj_color, amb_light);
	const t_color	i_diffuse = \
		calculate_diffuse_reflection(ray, to_light, light_source);
	const t_color	i_specular = \
		calculate_specular_reflection(ray, to_light, light_source, 1);

	return ((t_color){
		(int)fmin(i_ambient.red + i_diffuse.red + i_specular.red, 255),
		(int)fmin(i_ambient.green + i_diffuse.green + i_specular.green, 255),
		(int)fmin(i_ambient.blue + i_diffuse.blue + i_specular.blue, 255)
	});
}

static t_color	calculate_ambient_reflection(
					const t_color object_color,
					const t_ambient_light amb_light)
{
	const t_color	intensity = (t_color){
		(int)fmin(amb_light.color.red * amb_light.brightness, 255),
		(int)fmin(amb_light.color.green * amb_light.brightness, 255),
		(int)fmin(amb_light.color.blue * amb_light.brightness, 255) \
	};

	return ((t_color){
		object_color.red * intensity.red / 255,
		object_color.green * intensity.green / 255,
		object_color.blue * intensity.blue / 255
	});
}

static t_color	calculate_diffuse_reflection(
					const t_ray ray,
					const t_vec3 to_light,
					const t_light_source light_source)
{
	const t_color	intensity = (t_color){
		(int)fmin(light_source.color.red * light_source.brightness, 255),
		(int)fmin(light_source.color.green * light_source.brightness, 255),
		(int)fmin(light_source.color.blue * light_source.brightness, 255) \
	};
	const double	n_dot_l = fmax(0, vec3_dot_prod(ray.normal, to_light));

	return ((t_color){
		(int)(ray.obj_color.red * (intensity.red * n_dot_l) / 255),
		(int)(ray.obj_color.green * (intensity.green * n_dot_l) / 255),
		(int)(ray.obj_color.blue * (intensity.blue * n_dot_l) / 255)
	});
}

static t_color	calculate_specular_reflection(
					const t_ray ray,
					const t_vec3 to_light,
					const t_light_source light_source,
					const double smoothness)
{
	const t_color	intensity = (t_color){
		(int)fmin(light_source.color.red * light_source.brightness, 255),
		(int)fmin(light_source.color.green * light_source.brightness, 255),
		(int)fmin(light_source.color.blue * light_source.brightness, 255) \
	};
	const double	n_dot_l = fmax(0, vec3_dot_prod(ray.normal, to_light));
	const t_vec3	reflection = \
		vec3_norm(vec3_sub(vec3_mult(2 * n_dot_l, ray.normal), to_light));
	const double	r_dot_v = \
		fmax(0, vec3_dot_prod(reflection, vec3_mult(-1, ray.line.direction)));
	const double	powed_r_dot_v = pow(r_dot_v, smoothness);

	return ((t_color){
		(int)(ray.obj_color.red * intensity.red * powed_r_dot_v / 255),
		(int)(ray.obj_color.green * intensity.green * powed_r_dot_v / 255),
		(int)(ray.obj_color.blue * intensity.blue * powed_r_dot_v / 255)
	});
}
