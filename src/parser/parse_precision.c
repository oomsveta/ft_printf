/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 15:38:59 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/18 15:39:44 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * C23 7.23.6.1/4:
 * ---------------
 * The precision takes the form of a period (.) followed either by an
 * asterisk * (described later) or by an optional nonnegative decimal integer;
 * if only the period is specified, the precision is taken as zero.
 *
 * C23 7.23.6.1/5:
 * ---------------
 * As noted previously, a [...] precision [...] may be indicated by an asterisk.
 * In this case, an int argument supplies the [...] precision. [...] A negative
 * precision argument is taken as if the precision were omitted.
 */
bool	parse_precision(t_ctx *ctx)
{
	t_conversion_specifier	*specifier;
	int						precision;

	specifier = &ctx->current_specifier;
	specifier->has_precision = *specifier->cursor == '.';
	if (!specifier->has_precision)
	{
		return (true);
	}
	specifier->cursor += 1;
	if (*specifier->cursor == '*')
	{
		specifier->cursor += 1;
		precision = va_arg(ctx->args, int);
		specifier->precision = precision;
		if (precision < 0)
		{
			specifier->has_precision = false;
		}
		return (true);
	}
	return (parse_int(ctx, &specifier->precision));
}
