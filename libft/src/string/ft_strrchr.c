/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:33:29 by lwicket           #+#    #+#             */
/*   Updated: 2026/03/08 17:46:49 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	// provides ft_strlen, size_t

char	*ft_strrchr(const char *str, int chr)
{
	size_t	n;

	n = ft_strlen(str) + 1;
	chr = (unsigned char)chr;
	while (n--)
	{
		if (((unsigned char *)str)[n] == chr)
		{
			return ((char *)&str[n]);
		}
	}
	return (NULL);
}
