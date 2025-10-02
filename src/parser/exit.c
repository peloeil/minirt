/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:46:21 by sota              #+#    #+#             */
/*   Updated: 2025/09/15 22:11:13 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft/ft_string.h>

void	exit_with_message(const char msg[static 1])
{
	const size_t	len = ft_strlen(msg);
	ssize_t			byte;

	byte = write(STDERR_FILENO, "Error\n", 6);
	byte = write(STDERR_FILENO, msg, len);
	byte = write(STDERR_FILENO, "\n", 1);
	(void)byte;
	exit(EXIT_FAILURE);
}
