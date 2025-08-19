/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:56:50 by rogiso            #+#    #+#             */
/*   Updated: 2025/08/14 20:56:50 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minirt/scene.h>

void	free_2darray(void *array[static 1]);
void	assign_info_to_obj(const int i, const char info[static 1], t_scene *const obj);
void	assign_ambient_light_info(t_ambient_light *const node, const char info[static 1], const int i);
void	assign_camera_info(t_camera *const node, const char info[static 1], const int i);
void	assign_light_source_info(t_light_source *const node, const char info[static 1], const int i);
void	assign_sphere_info(t_sphere *const node, const char info[static 1], const int i);
void	assign_plane_info(t_plane *const node, const char info[static 1], const int i);
void	assign_cylinder_info(t_cylinder *const node, const char info[static 1], const int i);
int		parse_color(const char str[static 1]);
t_vec3	parse_vec3(const char str[static 1]);
double	parse_double(const char str[static 1]);
t_scene	*convert_line_into_object(const t_scene *const scene, const char line[static 1]);
t_scene	*parse_rt_file(const char file_path[static 1]);

#endif
