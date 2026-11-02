/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 18:30:34 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 21:30:19 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

void	flush_buffer(t_ctx *ctx)
{
	ssize_t	write_res;
	size_t	total_written;

	if (ctx->errno)
	{
		return ;
	}
	if (ctx->buffer.length == 0)
	{
		return ;
	}
	total_written = 0;
	while (ctx->buffer.length > 0)
	{
		write_res = write(STDOUT_FILENO, ctx->buffer.data + total_written, ctx->buffer.length);
		if (write_res == WRITE_ERROR)
		{
			ctx->errno = ERR_WRITE_FAILURE;
			return ;
		}
		ctx->buffer.length -= write_res;
		total_written += write_res;
	}
	ctx->total_written += total_written;
}

void	append_buffer(t_ctx *ctx, const char *str, size_t len)
{
	size_t	total_appended;
	size_t	copy_size;

	total_appended = 0;
	while (total_appended < len)
	{
		copy_size = ft_zmin(len - total_appended, PRINTF_BUFFER_SIZE - ctx->buffer.length);
		ft_memcpy(ctx->buffer.data + ctx->buffer.length, str + total_appended, copy_size);
		ctx->buffer.length += copy_size;
		total_appended += copy_size;
		if (ctx->buffer.length == PRINTF_BUFFER_SIZE)
		{
			flush_buffer(ctx);
			if (ctx->errno)
			{
				return ;
			}
		}
	}
}

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
			if (ctx->errno)
			{
				return ;
			}
		}
	}	
}

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

bool	print_formatted(t_ctx *ctx)
{
	const char	type = ctx->current_spec.type;
	char		formatting_buffer[64];

	if (type == '%')
	{
		put_percent(ctx);
	}
	else if (type == 'i' || type == 'd')
	{
		put_int(ctx);
	}
	else if (type == 'x' || type == 'X')
	{
		put_hex(ctx);
	}
	else if (type == 's')
	{
		put_str(ctx);
	}
	else if (type == 'p')
	{
		put_ptr(ctx);
	}
	else
	{
		append_buffer(ctx, formatting_buffer, convert_raw(ctx, formatting_buffer));
		return (true);
	}
	// return based on ctx->errno
	return (true);
}
