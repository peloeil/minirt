/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogiso <rogiso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:35:28 by rogiso            #+#    #+#             */
/*   Updated: 2025/09/08 20:35:28 by rogiso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include <minirt/scene.h>
# include <minirt/mlx_api.h>

void	render_scene(
			const t_scene *const scene,
			const t_display *const display);

#endif
