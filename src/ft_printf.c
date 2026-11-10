/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:34:51 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/04 16:09:01 by lwicket          ###   ########.fr       */
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
	if (ctx->error || ctx->total_written > INT_MAX)
	{
		return (-1);
	}
	return ((int)ctx->total_written);
}

static void	dispatch_conversion(t_ctx *ctx)
{
	static const t_put_fn		put_fns[] = {
	[CONV_RAW] = put_raw, [CONV_PERCENT] = put_percent,
	[CONV_INT] = put_int, [CONV_HEX] = put_hex, [CONV_STR] = put_str,
	[CONV_PTR] = put_ptr, [CONV_CHAR] = put_char, [CONV_UNSIGNED] = put_unsigned,
	};
	static const unsigned char	indices['x' - '%' + 1] = {
	['%' - '%'] = CONV_PERCENT, ['d' - '%'] = CONV_INT,
	['i' - '%'] = CONV_INT, ['x' - '%'] = CONV_HEX,
	['X' - '%'] = CONV_HEX, ['s' - '%'] = CONV_STR,
	['p' - '%'] = CONV_PTR, ['c' - '%'] = CONV_CHAR,
	['u' - '%'] = CONV_UNSIGNED,
	};
	size_t						i;

	i = (size_t)(unsigned char)ctx->current_spec.type - '%';
	if (i < sizeof indices)
	{
		put_fns[indices[i]](ctx);
	}
	else
	{
		put_raw(ctx);
	}
}

int	ft_printf(const char *format, ...)
{
	t_ctx		ctx;
	const char	*next;

	ctx = (t_ctx){0};
	va_start(ctx.args, format);
	while (!ctx.error && *format != '\0')
	{
		if (*format == '%')
		{
			if (!parse_conversion_specification(&ctx, format + 1))
			{
				break ;
			}
			dispatch_conversion(&ctx);
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
