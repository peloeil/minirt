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

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <math.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_vec3;

// vec3_util1.c
t_vec3	vec3_init(double x, double y, double z, int color);
bool	vec3_eq(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_sub(t_vec3 v1_from, t_vec3 v2_offset);
t_vec3	vec3_mult(t_vec3 v, double scalar);

// vec3_util2.c
double	vec3_abs(t_vec3 v);
double	vec3_dot_prod(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_cross_prod(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_norm(t_vec3 v);
double	vec3_rad(t_vec3 v1, t_vec3 v2);

#endif
