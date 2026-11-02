/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:42:30 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 21:46:21 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include <stdarg.h>

void	put_char(t_ctx *ctx)
{
	const char	c = (unsigned char)va_arg(ctx->args, int);

	ctx->current_spec.flags.pad_with_zeros = false;
	put_padded(ctx, &c, 1);
}
