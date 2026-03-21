/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlwr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 23:22:59 by lwicket           #+#    #+#             */
/*   Updated: 2026/03/08 23:23:31 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlwr(char *str)
{
	const char	*s0 = str;

	while (*str != '\0')
	{
		*str = ft_tolower(*str);
		str += 1;
	}
	return ((char *)s0);
}
