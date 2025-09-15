/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:41:49 by sota              #+#    #+#             */
/*   Updated: 2025/09/15 22:51:57 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser.h>
#include <stdlib.h>
#include <stdint.h>
#include <libft/ft_ctype.h>
#include <libft/ft_string.h>
#include <minirt/scene.h>

static uint8_t	parse_8bit_value(const char str[static 1])
{
	size_t			i;
	unsigned int	res;

	if (ft_strlen(str) > 3)
		exit_with_message("RGB value must be in [0,255]");
	i = 0;
	res = 0;
	while (ft_isdigit(str[i]))
	{
		res = 10 * res + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		exit_with_message("invalid character in a color string");
	if (res > 0xff)
		exit_with_message("RGB value must be in [0,255]");
	return ((uint8_t)res);
}

t_color	parse_color(const char str[static 1])
{
	const char *const *const	rgb = (const char **)ft_split(str, ',');
	size_t						i;
	t_color						color;

	if (rgb == NULL)
		exit_with_message("malloc() failed");
	i = 0;
	if (rgb[i] != NULL)
		color.red = parse_8bit_value(rgb[i++]);
	if (rgb[i] != NULL)
		color.green = parse_8bit_value(rgb[i++]);
	if (rgb[i] != NULL)
		color.blue = parse_8bit_value(rgb[i++]);
	if (i != 3)
		exit(EXIT_FAILURE);
	free_2darray((void **)rgb);
	return (color);
}
