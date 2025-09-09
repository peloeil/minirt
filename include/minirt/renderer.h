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

# include <stddef.h>
# include <minirt/scene.h>

typedef struct s_pixel
{
	int		x;
	int		y;
	t_color	color;
}	t_pixel;

#endif
