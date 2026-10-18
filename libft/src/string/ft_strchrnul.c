/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrnul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 23:04:57 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/18 14:55:44 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrnul(const char *str, int chr)
{
	chr = (unsigned char)chr;
	while (*str != '\0' && *(unsigned char *)str != chr)
	{
		str += 1;
	}
	return ((char *)str);
}
