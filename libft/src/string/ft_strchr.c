/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 19:05:07 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/18 14:55:39 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>	// provides NULL, size_t

char	*ft_strchr(const char *str, int chr)
{
	chr = (unsigned char)chr;
	while (*(unsigned char *)str != chr)
	{
		if (*str == '\0')
		{
			return (NULL);
		}
		str += 1;
	}
	return ((char *)str);
}
