/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_raw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 17:29:23 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 20:53:53 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <stddef.h>

// #'+-I
// #' -I
// #'+0I

static char	*restore_flags(t_ctx *ctx, char *buffer)
{
	const t_flags	flags = ctx->current_specifier.flags;

	if (flags.alternate_form)
	{
		*buffer++ = '#';
	}
	if (flags.force_sign)
	{
		*buffer++ = '+';
	}
	if (flags.reserve_sign_space)
	{
		*buffer++ = ' ';
	}
	if (flags.left_justify)
	{
		*buffer++ = '-';
	}
	if (flags.pad_with_zeros)
	{
		*buffer++ = '0';
	}
	return buffer;;
}

size_t	convert_raw(t_ctx *ctx, char *buffer)
{
	const char  *t0 = buffer;

	*buffer++ = '%';
	buffer = restore_flags(ctx, buffer);
	if (ctx->current_specifier.width)
	{
		ft_jutoa(ctx->current_specifier.width, buffer, 10);
		buffer = ft_strchr(buffer, '\0');
	}
	if (ctx->current_specifier.has_precision)
	{
		*buffer++ = '.';
		ft_jutoa(ctx->current_specifier.precision, buffer, 10);
		buffer = ft_strchr(buffer, '\0');
	}
	*buffer++ = ctx->current_specifier.type;
	*buffer = '\0';
	return ft_strlen(t0);
}
