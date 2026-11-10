/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 22:05:29 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/07 16:33:59 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"

/**
 * @brief Appends the string @p str of length @p len to ft_printf's buffer.
 *
 * If there isn't enough room left in the buffer, the string is copied in
 * chunks: each time the buffer becomes full, it is flushed, until the whole
 * string has been appended.
 *
 * @param ctx Pointer to the context.
 * @param str The string to append to the buffer.
 * @param len The length of the string to append.
 */
void	append_buffer(t_ctx *ctx, const char *str, size_t len)
{
	size_t	room_left;
	size_t	copy_size;

	while (len > 0)
	{
		room_left = sizeof ctx->buffer.data - ctx->buffer.length;
		copy_size = ft_zmin(len, room_left);
		ft_memcpy(ctx->buffer.data + ctx->buffer.length, str, copy_size);
		ctx->buffer.length += copy_size;
		str += copy_size;
		len -= copy_size;
		if (ctx->buffer.length == sizeof ctx->buffer.data)
		{
			flush_buffer(ctx);
			if (ctx->error)
			{
				return ;
			}
		}
	}
}
