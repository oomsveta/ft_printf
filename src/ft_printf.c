/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:34:51 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 21:54:04 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internals.h"
#include "libft.h"
#include <limits.h>
#include <stdarg.h>

static inline int	exit_printf(t_ctx *ctx)
{
	flush_buffer(ctx);
	va_end(ctx->args);
	if (ctx->errno || ctx->total_written > INT_MAX)
	{
		return (-1);
	}
	return ((int)ctx->total_written);
}

int	ft_printf(const char *format, ...)
{
	t_ctx		ctx;
	const char	*next;

	ctx = (t_ctx){0};
	va_start(ctx.args, format);
	while (!ctx.errno && *format != '\0')
	{
		if (*format == '%')
		{
			if (!parse_conversion_specification(&ctx, format + 1))
			{
				break ;
			}
			print_formatted(&ctx);
			format = ctx.current_spec.cursor;
		}
		else
		{
			next = ft_strchrnul(format, '%');
			append_buffer(&ctx, format, next - format);
			format = next;
		}
	}
	return (exit_printf(&ctx));
}
