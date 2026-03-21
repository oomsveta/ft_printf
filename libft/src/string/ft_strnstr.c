/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:57:18 by lwicket           #+#    #+#             */
/*   Updated: 2026/03/22 12:28:24 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	// provides ft_strlen, ft_strncmp, NULL, size_t

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	const size_t	need_len = ft_strlen(needle);

	if (need_len == 0)
	{
		return ((char *)haystack);
	}
	i = 0;
	while ((i + need_len) <= len && haystack[i] != '\0')
	{
		if (ft_strncmp(&haystack[i], needle, need_len) == 0)
		{
			return ((char *)&haystack[i]);
		}
		i += 1;
	}
	return (NULL);
}
