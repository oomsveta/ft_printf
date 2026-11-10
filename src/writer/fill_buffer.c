/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 22:14:58 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/07 16:34:06 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"

/**
 * @brief Appends @p n copies of the character @p c to ft_printf's buffer.
 *
 * Useful for writing padding.
 *
 * If there is not enough room left in the buffer to hold @p n more characters,
 * the buffer is flushed and the characters are appended in chunks in a loop
 * until all characters have been appended.
 *
 * @param ctx Pointer to the context.
 * @param c   The character to fill the buffer with.
 * @param n   How many times to repeat @p c.
 */
void	fill_buffer(t_ctx *ctx, char c, size_t n)
{
	size_t	room_left;
	size_t	len;

	while (n > 0)
	{
		room_left = sizeof ctx->buffer.data - ctx->buffer.length;
		len = ft_zmin(n, room_left);
		ft_memset(ctx->buffer.data + ctx->buffer.length, c, len);
		ctx->buffer.length += len;
		n -= len;
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
