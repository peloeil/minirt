/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:41:49 by sota              #+#    #+#             */
/*   Updated: 2025/08/19 22:42:22 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser.h>
#include <stdlib.h>
#include <stdint.h>
#include <libft/ft_ctype.h>
#include <libft/ft_string.h>

static uint8_t	parse_8bit_value(const char str[static 1])
{
	size_t			i;
	unsigned int	res;

	if (ft_strlen(str) > 3)
		exit(EXIT_FAILURE);
	i = 0;
	res = 0;
	while (ft_isdigit(str[i]))
	{
		res = 10 * res + str[i] - '0';
		i++;
	}
	if (str[i] != '\0' || res > 0xff)
		exit(EXIT_FAILURE);
	return ((uint8_t)res);
}

t_color	parse_color(const char str[static 1])
{
	const char *const *const	rgb = (const char **)ft_split(str, ',');
	size_t						i;
	t_color						color;

	if (rgb == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (rgb[i] != NULL)
	{
		if (i == 0)
			color.red = parse_8bit_value(rgb[i]);
		if (i == 1)
			color.green = parse_8bit_value(rgb[i]);
		if (i == 2)
			color.blue = parse_8bit_value(rgb[i]);
		i++;
	}
	if (i != 3)
		exit(EXIT_FAILURE);
	free_2darray((void **)rgb);
	return (color);
}
