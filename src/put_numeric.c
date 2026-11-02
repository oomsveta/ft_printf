/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_numeric.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 14:20:15 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 21:30:19 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <stddef.h>

/**
 * [spaces][prefix][zeros][digits]  (right-justified, default)
 * [prefix][zeros][digits][spaces]  ('-' flag)
 */
static inline t_padding	compute_padding(
	const t_spec *spec, size_t prefix_len, size_t digits_len
)
{
	t_padding	padding;
	size_t		total_len;

	padding = (t_padding){0};
	if (spec->has_precision && (size_t)spec->precision > digits_len)
	{
		padding.zeros = (size_t)spec->precision - digits_len;
	}
	total_len = prefix_len + padding.zeros + digits_len;
	if ((size_t)spec->width > total_len)
	{
		if (spec->flags.pad_with_zeros && !spec->has_precision)
		{
			padding.zeros += (size_t)spec->width - total_len;
		}
		else
		{
			padding.spaces = (size_t)spec->width - total_len;
		}
	}
	return (padding);
}

void	put_numeric(t_ctx *ctx, const char *digits, const char *prefix)
{
	const size_t	prefix_len = ft_strlen(prefix);
	const size_t	digits_len = ft_strlen(digits);
	const t_spec	*spec = &ctx->current_spec;
	const t_padding	padding = compute_padding(spec, prefix_len, digits_len);

	if (!spec->flags.left_justify)
	{
		fill_buffer(ctx, ' ', padding.spaces);
	}
	append_buffer(ctx, prefix, prefix_len);
	fill_buffer(ctx, '0', padding.zeros);
	append_buffer(ctx, digits, digits_len);
	if (spec->flags.left_justify)
	{
		fill_buffer(ctx, ' ', padding.spaces);
	}
}
