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
	t_vec3	intersection;
	t_vec3	normal;
	t_scene	*target_object;
	bool	exists;
}	t_ray;

// core.c
t_quad_root	solve_quadratic_equation(const t_quad_coefs coefs);
t_vec3		find_ray_intersection(
				const t_line line,
				const t_quad_root quad_root);

// plane.c
t_ray		find_plane_ray_intersection(
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

#endif
