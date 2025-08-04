/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:30:05 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/04 16:30:05 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <stdbool.h>
# include <math.h>
# define EPSILON 0.001

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_vec3;

// vec3_util1.c
t_vec3	vec3_init(const double x, const double y, const double z, const int color);
bool	vec3_eq(const t_vec3 v1, const t_vec3 v2);
t_vec3	vec3_add(const t_vec3 v1, const t_vec3 v2);
t_vec3	vec3_sub(const t_vec3 v1_from, const t_vec3 v2_offset);
t_vec3	vec3_mult(const double scalar, const t_vec3 v);

// vec3_util2.c
double	vec3_abs(const t_vec3 v);
double	vec3_dot_prod(const t_vec3 v1, const t_vec3 v2);
t_vec3	vec3_cross_prod(const t_vec3 v1, const t_vec3 v2);
t_vec3	vec3_norm(const t_vec3 v);
double	vec3_rad(const t_vec3 v1, const t_vec3 v2);

#endif
