/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:05:38 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/04 18:05:38 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <vec3.h>

typedef struct s_line
{
	t_vec3	position;
	t_vec3	direction;
}	t_line;

typedef struct s_plane
{
	t_vec3	position;
	t_vec3	normal;
	int		color;
}	t_plane;

typedef struct s_sphere
{
	double	radius;
	t_vec3	center;
	int		color;
}	t_sphere;

typedef struct s_cylinder
{
	double	radius;
	double	height;
	t_vec3	center;
	t_line	axis;
	int		color;
}	t_cylinder;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	double	radian;
}	t_camera;

typedef struct s_ambient_light
{
	int		color;
	double	brightness;
}	t_ambient_light;

typedef struct s_light_source
{
	t_vec3	position;
	double	brightness;
	int		color;
}	t_light_source;

#endif
