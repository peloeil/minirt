/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:30:05 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/18 16:30:05 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACING_H
# define RAY_TRACING_H

# include <stdbool.h>
# include <minirt/vec3.h>
# include <minirt/scene.h>
# define SMOOTHNESS 10

typedef struct s_quad_coefs
{
	double	a;
	double	b;
	double	c;
}	t_quad_coefs;

typedef struct s_quad_root
{
	double	root_large;
	double	root_small;
}	t_quad_root;

typedef struct s_ray
{
	t_line	line;
	double	line_t_coef;
	t_vec3	intersection;
	t_vec3	hit_normal;
	t_color	color;
	t_tag	hit_object;
}	t_ray;

// core.c
t_quad_root	solve_quadratic_equation(const t_quad_coefs coefs);
double		select_nearest_line_t_coef(const t_quad_root quad_root);
t_vec3		calculate_ray_intersection(
				const t_line line,
				const double line_t_coef);

// ray_tracing.c
t_ray		find_nearest_ray_intersection(
				const t_line line,
				const t_scene *const scene);

// plane.c
t_ray		find_plane_ray_intersection(
				const t_line line,
				const t_plane plane);
double		solve_plane_equation(
				const t_line line,
				const t_plane plane);

// sphere.c
t_ray		find_sphere_ray_intersection(
				const t_line line,
				const t_sphere sphere);

// cylinder.c
t_ray		find_cylinder_ray_intersection(
				const t_line line,
				const t_cylinder cylinder);

// phong_reflection.c
t_color		calculate_phong_reflection(
				const t_ray ray,
				const t_scene *const scene,
				const t_ambient_light amb_light,
				const t_light_source light_source);

#endif
