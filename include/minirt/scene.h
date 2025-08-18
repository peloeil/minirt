/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:05:38 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/14 18:05:38 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <libft/ft_list.h>
# include <minirt/vec3.h>

typedef	t_list t_scene;

typedef enum e_tag
{
	LINE,
	PLANE,
	SPHERE,
	CYLINDER,
	CAMERA,
	AMBIENT_LIGHT,
	LIGHT_SOURCE
}	t_tag;

typedef struct s_line
{
	t_tag	tag;
	t_vec3	position;
	t_vec3	direction;
}	t_line;

typedef struct s_plane
{
	t_tag	tag;
	t_vec3	position;
	t_vec3	normal;
	int		color;
}	t_plane;

typedef struct s_sphere
{
	t_tag	tag;
	double	radius;
	t_vec3	center;
	int		color;
}	t_sphere;

typedef struct s_cylinder
{
	t_tag	tag;
	double	radius;
	double	height;
	t_vec3	bottom_center;
	t_vec3	axis;
	int		color;
}	t_cylinder;

typedef struct s_camera
{
	t_tag	tag;
	t_vec3	position;
	t_vec3	direction;
	double	radian;
}	t_camera;

typedef struct s_ambient_light
{
	t_tag	tag;
	int		color;
	double	brightness;
}	t_ambient_light;

typedef struct s_light_source
{
	t_tag	tag;
	t_vec3	position;
	double	brightness;
	int		color;
}	t_light_source;

#endif
