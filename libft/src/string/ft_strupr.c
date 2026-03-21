/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 23:22:06 by lwicket           #+#    #+#             */
/*   Updated: 2026/03/08 23:24:13 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupr(char *str)
{
	const char	*s0 = str;

	while (*str != '\0')
	{
		*str = ft_toupper(*str);
		str += 1;
	}
	return ((char *)s0);
}
