/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:00:51 by lwicket           #+#    #+#             */
/*   Updated: 2026/03/22 12:27:05 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline void	*baby_memchr(
	const unsigned char *mem, unsigned char chr, size_t n
)
{
	while (n--)
	{
		if (*mem == chr)
		{
			return ((void *)mem);
		}
		mem += 1;
	}
	return (NULL);
}

static inline void	*test_word(
	const unsigned char *mem, t_word value, int chr, t_word broadcast
)
{
	const t_word	ones = (t_word)-1 / 255;
	const t_word	high = ones << 7;
	const t_word	diff = value ^ broadcast;

	if ((diff - ones) & ~diff & high)
	{
		return (baby_memchr(mem, chr, sizeof(t_word)));
	}
	return (NULL);
}

void	*ft_memchr(const void *mem, int chr, size_t n)
{
	const size_t		align = -(uintptr_t)mem & (sizeof(t_word) - 1);
	const unsigned char	*end = (const unsigned char *)mem + n;
	const unsigned char	*ptr = mem;
	t_word				broadcast;
	void				*match;

	if (n < sizeof(t_word))
		return (baby_memchr(mem, chr, n));
	broadcast = (t_word)-1 / 255 * (unsigned char)chr;
	match = test_word(ptr, *(t_word *)ptr, chr, broadcast);
	if (match)
		return (match);
	ptr += align;
	n -= align;
	while (n >= sizeof(t_word))
	{
		match = test_word(ptr, *(t_aligned_word *)ptr, chr, broadcast);
		if (match)
			return (match);
		ptr += sizeof(t_word);
		n -= sizeof(t_word);
	}
	return (test_word(end - sizeof(t_word), *(t_word *)ptr, chr, broadcast));
}
