/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 22:23:39 by lwicket           #+#    #+#             */
/*   Updated: 2026/03/08 17:36:28 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	// provides ft_isalnum, ft_isalpha, ft_isdigit

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
