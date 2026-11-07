/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 22:40:12 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/07 16:34:08 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include <unistd.h>

/**
 * @brief Flushes ft_printf's internal buffer.
 *
 * Writes the contents of the context's buffer to @c STDOUT_FILENO, retrying on
 * partial writes. Then empties the buffer (sets its length to 0) and updates
 * @c ctx->total_written accordingly.
 *
 * If a call to write(2) fails, the function sets @c ctx->error to
 * @c ERR_WRITE_FAILURE and returns without updating @c ctx->total_written.
 *
 * @param ctx Pointer to the context.
 *
 * @note flush_buffer does nothing if @c ctx->error is already set.
 */
void	flush_buffer(t_ctx *ctx)
{
	ssize_t	bytes_written;
	size_t	total_written;

	if (ctx->error)
	{
		return ;
	}
	total_written = 0;
	while (ctx->buffer.length > 0)
	{
		bytes_written = write(
				STDOUT_FILENO,
				ctx->buffer.data + total_written,
				ctx->buffer.length);
		if (bytes_written == -1)
		{
			ctx->error = ERR_WRITE_FAILURE;
			return ;
		}
		ctx->buffer.length -= bytes_written;
		total_written += bytes_written;
	}
	ctx->total_written += total_written;
}
