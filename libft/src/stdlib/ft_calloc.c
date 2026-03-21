/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:42:15 by lwicket           #+#    #+#             */
/*   Updated: 2026/03/08 17:35:44 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>	// provides ENOMEM, errno
#include <stdlib.h>	// provides malloc, NULL, size_t
#include "libft.h"	// provides ft_bzero, SIZE_MAX

void	*ft_calloc(size_t nbr_of_elements, size_t element_size)
{
	void	*buffer;
	size_t	total_size;

	if (element_size != 0 && nbr_of_elements > SIZE_MAX / element_size)
	{
		errno = ENOMEM;
		return (NULL);
	}
	total_size = nbr_of_elements * element_size;
	buffer = malloc(total_size);
	if (buffer == NULL)
	{
		return (NULL);
	}
	ft_bzero(buffer, total_size);
	return (buffer);
}
