/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_padded.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 22:24:38 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/07 16:34:10 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"

/**
 * @brief Appends a string to ft_printf's buffer, padded according to the
 *        current conversion specification.
 *
 * Computes the length and character of the padding, then puts the string @p str
 * of length @p len into the buffer, adding the padding before or after it if
 * necessary.
 *
 * @param ctx Pointer to the context.
 * @param str The string to append to the buffer, padding not included.
 * @param len The length of the string @p str, padding not included.
 */
void	put_padded(t_ctx *ctx, const char *str, size_t len)
{
	const t_spec	*spec = &ctx->current_spec;
	char			padding_char;
	size_t			padding_len;

	padding_len = 0;
	if ((size_t)spec->width > len)
	{
		padding_len = (size_t)spec->width - len;
	}
	padding_char = ' ';
	if (spec->flags.pad_with_zeros)
	{
		padding_char = '0';
	}
	if (!spec->flags.left_justify)
	{
		fill_buffer(ctx, padding_char, padding_len);
	}
	append_buffer(ctx, str, len);
	if (spec->flags.left_justify)
	{
		fill_buffer(ctx, padding_char, padding_len);
	}
}
