/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:42:00 by sota              #+#    #+#             */
/*   Updated: 2025/09/15 20:24:31 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/vec3.h>
#include <minirt/parser.h>
#include <stdlib.h>
#include <libft/ft_string.h>

static int	num_of_comma(const char str[static 1])
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

t_vec3	parse_vec3(const char str[static 1])
{
	const char *const *const	xyz = (const char **)ft_split(str, ',');
	size_t						i;
	t_vec3						res;

	if (xyz == NULL)
		exit_with_message("malloc() failed");
	if (num_of_comma(str) != 2)
		exit_with_message("invalid number of fields in a vector string");
	i = 0;
	if (xyz[i] != NULL)
		res.x = parse_double(xyz[i++]);
	if (xyz[i] != NULL)
		res.y = parse_double(xyz[i++]);
	if (xyz[i] != NULL)
		res.z = parse_double(xyz[i++]);
	if (i != 3)
		exit_with_message("invalid number of fields in a vector string");
	free_2darray((void **)xyz);
	return (res);
}
