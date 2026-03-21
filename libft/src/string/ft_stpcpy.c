/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stpcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 23:15:12 by lwicket           #+#    #+#             */
/*   Updated: 2026/03/08 23:15:21 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_stpcpy(char *restrict dest, const char *restrict src)
{
	while (*src != '\0')
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (dest);
}
