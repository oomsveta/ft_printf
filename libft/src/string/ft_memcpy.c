/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 21:14:43 by lwicket           #+#    #+#             */
/*   Updated: 2026/03/22 12:22:01 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	// provides size_t, t_aligned_word, t_word

static inline void	baby_memcpy(
	unsigned char *dest, const unsigned char *src, size_t n
)
{
	while (n--)
	{
		*dest++ = *src++;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				align;
	unsigned char		*d;
	const unsigned char	*s = src;

	if (n < sizeof(t_word))
	{
		baby_memcpy(dest, src, n);
		return (dest);
	}
	d = dest;
	*(t_word *)d = *(t_word *)s;
	*(t_word *)(d + n - sizeof(t_word)) = *(t_word *)(s + n - sizeof(t_word));
	align = -(uintptr_t)dest & (sizeof(t_word) - 1);
	d += align;
	s += align;
	n -= align;
	while (n >= sizeof(t_word))
	{
		*(t_aligned_word *)d = *(t_word *)s;
		d += sizeof(t_word);
		s += sizeof(t_word);
		n -= sizeof(t_word);
	}
	return (dest);
}
