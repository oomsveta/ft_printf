/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_raw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 17:29:23 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/31 12:26:45 by lwicket          ###   ########.fr       */
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
		ft_itoa(ctx->current_specifier.width, buffer);
		buffer = ft_strchr(buffer, '\0');
	}
	if (ctx->current_specifier.has_precision)
	{
		*buffer++ = '.';
		ft_itoa(ctx->current_specifier.precision, buffer);
		buffer = ft_strchr(buffer, '\0');
	}
	*buffer++ = ctx->current_specifier.type;
	*buffer = '\0';
	return ft_strlen(t0);
}
