/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zmin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:09:05 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/18 14:55:13 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * @brief Returns the smaller of two size_t values.
 *
 * This function compares two unsigned integral values and returns the lesser of
 * the two.
 *
 * @param a First value to compare.
 * @param b Second value to compare.
 * @return The smaller of @p a and @p b.
 */
size_t	ft_zmin(size_t a, size_t b)
{
	if (a <= b)
	{
		return (a);
	}
	return (b);
}
