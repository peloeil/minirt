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

double	vec3_abs(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	vec3_dot_prod(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vec3_cross_prod(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x,
		0});
}

t_vec3	vec3_norm(t_vec3 v)
{
	const double	v_abs = vec3_abs(v);

	return ((t_vec3){v.x / v_abs, v.y / v_abs, v.z / v_abs, 0});
}

double	vec3_rad(t_vec3 v1, t_vec3 v2)
{
	const double	v1_abs = vec3_abs(v1);
	const double	v2_abs = vec3_abs(v2);
	const double	v_dot_prod = vec3_dot_prod(v1, v2);
	const double	cos = v_dot_prod / (v1_abs * v2_abs);

	return (acos(cos));
}
