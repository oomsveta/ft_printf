/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_raw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 17:29:23 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 22:25:18 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <limits.h>
#include <stddef.h>

static inline char	*restore_flags(t_flags flags, char *buffer)
{
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
	return (buffer);
}

void	put_raw(t_ctx *ctx)
{
	const t_spec	*spec = &ctx->current_spec;
	char			buffer[128];
	char			*cursor;

	buffer[0] = '%';
	cursor = restore_flags(spec->flags, buffer + 1);
	if (spec->width)
	{
		cursor = ft_strchr(ft_jutoa(spec->width, cursor, 10), '\0');
	}
	if (spec->has_precision)
	{
		*cursor++ = '.';
		cursor = ft_strchr(ft_jutoa(spec->precision, cursor, 10), '\0');
	}
	if (spec->type != '\0')
	{
		*cursor++ = spec->type;
	}
	append_buffer(ctx, buffer, cursor - buffer);
}
