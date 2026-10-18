/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 15:38:50 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/18 15:40:34 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * C23 7.23.6.1/4:
 * ---------------
 * The field width takes the form of an asterisk * (described later) or a
 * nonnegative decimal integer.
 *
 * C23 7.23.6.1/5:
 * ---------------
 * As noted previously, a field width [...] may be indicated by an asterisk. In
 * this case, an int argument supplies the field width. [...] A negative field
 * width argument is taken as a - flag followed by a positive field width.
 */
bool	parse_width(t_ctx *ctx)
{
	t_conversion_specifier	*specifier;
	int						width;

	specifier = &ctx->current_specifier;
	if (*specifier->cursor == '*')
	{
		specifier->cursor += 1;
		width = va_arg(ctx->args, int);
		specifier->width = (int)ft_abs(width);
		if (width < 0)
		{
			specifier->flags.left_justify = true;
			specifier->flags.pad_with_zeros = false;
			if (width == INT_MIN)
			{
				ctx->errno = ERR_INT_OVERFLOW;
				return (false);
			}
		}
		return (true);
	}
	return (parse_int(ctx, &specifier->width));
}
