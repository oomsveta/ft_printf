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
	size_t	total_appended;
	size_t	len;

	total_appended = 0;
	while (total_appended < n)
	{
		len = ft_zmin(n - total_appended, PRINTF_BUFFER_SIZE - ctx->buffer.length);
		ft_memset(ctx->buffer.data + ctx->buffer.length, c, len);
		ctx->buffer.length += len;
		total_appended += len;
		if (ctx->buffer.length == PRINTF_BUFFER_SIZE)
		{
			flush_buffer(ctx);
			if (ctx->error)
			{
				return ;
			}
		}
	}	
}
