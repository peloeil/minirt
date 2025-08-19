/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 01:18:31 by sota              #+#    #+#             */
/*   Updated: 2025/08/20 01:19:23 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_2darray(void **array)
{
	size_t	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free((void *)array);
}
