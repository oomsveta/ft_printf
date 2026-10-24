/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_percent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 18:28:48 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/24 10:15:13 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include <stddef.h>

size_t	convert_percent(t_ctx *ctx, char *buffer)
{
	(void)ctx;
	buffer[0] = '%';
	return (1);
}
