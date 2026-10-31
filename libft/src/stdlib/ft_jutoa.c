/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jutoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 17:34:08 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 20:58:05 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	// provides ft_memcpy
#include <limits.h>	// provides CHAR_BIT
#include <stdint.h>	// provides uintmax_t

char	*ft_jutoa(uintmax_t n, char *dest, int radix)
{
	const char	*digits = "0123456789abcdefghijklmnopqrstuvwxyz";
	char		scratchpad[sizeof(uintmax_t) * CHAR_BIT + 1];
	char		*cursor;

	if (radix < 2 || radix > 36)
	{
		*dest = '\0';
		return (dest);
	}
	cursor = scratchpad + sizeof scratchpad;
	*--cursor = '\0';
	while (n >= (uintmax_t)radix)
	{
		*--cursor = digits[n % radix];
		n /= radix;
	}
	*--cursor = digits[n % radix];
	return (ft_memcpy(dest, cursor, (scratchpad + sizeof scratchpad) - cursor));
}
