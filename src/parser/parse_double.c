/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:41:55 by sota              #+#    #+#             */
/*   Updated: 2025/08/19 22:42:22 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <libft/ft_ctype.h>

static double	parse_integral_part(const char str[static 1])
{
	size_t	i;
	double	res;

	i = 0;
	res = 0.0;
	while (ft_isdigit(str[i]))
		res = 10 * res + str[i++] - '0';
	return (res);
}

static double	parse_fractional_part(const char str[static 1])
{
	size_t	i;
	size_t	point_idx;
	double	res;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	if (str[i++] != '.')
		exit(EXIT_FAILURE);
	point_idx = i - 1;
	res = 0.0;
	while (ft_isdigit(str[i]))
	{
		res += (str[i] - '0') * pow(10.0, (double)point_idx - (double)i);
		i++;
	}
	if (str[i] != '\0')
		exit(EXIT_FAILURE);
	return (res);
}

double	parse_double(const char str[static 1])
{
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	if (str[0] == '+' || str[0] == '-')
		sign = ('-' + '+' - 2 * str[i++]) / ('-' - '+');
	return (sign
		* (parse_integral_part(&str[i])
			+ parse_fractional_part(&str[i])
		));
}
