/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:28:03 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/04 16:28:03 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/vec3.h>
#include <math.h>

double	vec3_abs(const t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	vec3_dot_prod(const t_vec3 v1, const t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vec3_cross_prod(const t_vec3 v1, const t_vec3 v2)
{
	return ((t_vec3){
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x});
}

t_vec3	vec3_norm(const t_vec3 v)
{
	const double	v_abs = vec3_abs(v);

	if (v_abs == 0.0)
		return ((t_vec3){0, 0, 0});
	return ((t_vec3){v.x / v_abs, v.y / v_abs, v.z / v_abs});
}

double	vec3_rad(const t_vec3 v1, const t_vec3 v2)
{
	const double	v1_abs = vec3_abs(v1);
	const double	v2_abs = vec3_abs(v2);
	const double	v_dot_prod = vec3_dot_prod(v1, v2);

	if (v1_abs == 0.0 || v2_abs == 0.0)
		return (0.0);
	return (acos(fmax(-1.0, fmin(v_dot_prod / (v1_abs * v2_abs), 1.0))));
}
