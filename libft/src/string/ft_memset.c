/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 22:42:39 by lwicket           #+#    #+#             */
/*   Updated: 2026/03/22 12:22:44 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	// provides size_t, t_aligned_word, t_word

static inline void	byte_by_byte_memset(
	unsigned char *buffer, unsigned char byte, size_t size
)
{
	while (size--)
	{
		*buffer++ = byte;
	}
}

void	*ft_memset(void *buffer, int byte, size_t size)
{
	t_word			filler;
	unsigned char	*ptr;
	size_t			align;

	if (size < sizeof(t_word))
	{
		byte_by_byte_memset(buffer, byte, size);
		return (buffer);
	}
	ptr = buffer;
	filler = (t_word)-1 / 255 * (unsigned char)byte;
	*(t_word *)ptr = filler;
	*(t_word *)(ptr + size - sizeof(t_word)) = filler;
	align = -(uintptr_t)buffer & (sizeof(t_word) - 1);
	ptr += align;
	size -= align;
	while (size >= sizeof(t_word))
	{
		*(t_aligned_word *)ptr = filler;
		ptr += sizeof(t_word);
		size -= sizeof(t_word);
	}
	return (buffer);
}
