/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:34:51 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/24 10:16:06 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internals.h"
#include <stdarg.h>

static int	exit_printf(t_ctx *ctx)
{
	if (!ctx->errno)
	{
		flush_buffer(ctx);
		// TODO should ensure that the last flush didn't result in an error
		return ((int)ctx->total_written);
	}
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	t_ctx			ctx;

	ctx = (t_ctx){0};
	va_start(ctx.args, format);
	while (!ctx.errno && *format != '\0')
	{
		if (*format == '%')
		{
			if (!parse_conversion_spec(&ctx, format + 1))
			{
				break ;
			}
			if (!print_formatted(&ctx))
			{
				continue ;
			}
			format = ctx.current_spec.cursor;
		}
		else
		{
			// maybe advance to the next % using strchr
			append_buffer(&ctx, format, 1);
			format += 1;
		}
	}
	return (exit_printf(&ctx));
}
