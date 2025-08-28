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

# include <stdint.h>
# include <libft/ft_list.h>
# include <minirt/vec3.h>

typedef t_list	t_scene;

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

typedef struct s_color
{
	uint8_t	R;
	uint8_t	G;
	uint8_t	B;
}	t_color;

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
	t_color	color;
}	t_plane;

typedef struct s_sphere
{
	t_tag	tag;
	double	radius;
	t_vec3	center;
	t_color	color;
}	t_sphere;

typedef struct s_cylinder
{
	t_tag	tag;
	t_vec3	center;
	t_vec3	axis;
	double	radius;
	double	height;
	t_color	color;
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
	double	brightness;
	t_color	color;
}	t_ambient_light;

typedef struct s_light_source
{
	t_tag	tag;
	t_vec3	position;
	double	brightness;
	t_color	color;
}	t_light_source;

#endif
