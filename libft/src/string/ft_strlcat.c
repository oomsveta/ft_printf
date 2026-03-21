/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:32:58 by lwicket           #+#    #+#             */
/*   Updated: 2026/03/08 18:58:07 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	// provides ft_strlcpy, ft_strlen, ft_strnlen

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	const size_t	dest_len = ft_strnlen(dest, size);

	if (dest_len == size)
	{
		return (dest_len + ft_strlen(src));
	}
	return (dest_len + ft_strlcpy(dest + dest_len, src, size - dest_len));
}
