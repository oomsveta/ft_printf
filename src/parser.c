/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:04:14 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/18 15:33:21 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>

void	parse_flags(t_ctx *ctx)
{
	t_flags		flags;
	const char	*str = ctx->current_specifier.cursor;

	flags = (t_flags){0};
	while (true)
	{
		if (*str == '-')
			flags.left_justify = true;
		else if (*str == '+')
			flags.force_sign = true;
		else if (*str == ' ')
			flags.reserve_sign_space = true;
		else if (*str == '0')
			flags.pad_with_zeros = true;
		else if (*str == '#')
			flags.alternate_form = true;
		else if (*ft_strchrnul(IGNORED_FLAGS, *str) == '\0')
			break ;
		str += 1;
	}
	flags.reserve_sign_space &= !flags.force_sign;
	flags.pad_with_zeros &= !flags.left_justify;
	ctx->current_specifier.flags = flags;
}

static bool	parse_int(t_ctx *ctx, int *res)
{
	int			acc;
	int			digit;
	const char	*nptr = ctx->current_specifier.cursor;
	const int	cutoff = INT_MAX / 10;
	const int	cutlim = INT_MAX % 10;

	acc = 0;
	while (ft_isdigit(*nptr))
	{
		digit = ft_digittoint(*nptr);
		if (acc > cutoff || (acc == cutoff && digit > cutlim))
		{
			ctx->errno = ERR_INT_OVERFLOW;
			*res = INT_MIN;
			return (false);
		}
		acc = acc * 10 + digit;
		nptr += 1;
	}
	ctx->current_specifier.cursor = nptr;
	*res = acc;
	return (true);
}

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

/**
 * Unsupported; just skip length modifiers
 */
void	parse_length(t_ctx *ctx)
{
	const char	*cursor = ctx->current_specifier.cursor;

	if (*cursor == 'l' || *cursor == 'h' || *cursor == 'D')
	{
		cursor += 1 + (cursor[0] == cursor[1]);
	}
	else if (ft_strchr("jztLH", *cursor))
	{
		cursor += 1;
	}
	else if (*cursor == 'w')
	{
		cursor += 1 + (cursor[1] == 'f');
		if (*cursor == '0' || !ft_isdigit(*cursor))
		{
			return ;
		}
		while (ft_isdigit(*cursor))
		{
			cursor += 1;
		}
	}
	ctx->current_specifier.cursor = cursor;
}

bool	parse_conversion_specifier(t_ctx *ctx, const char *str)
{
	ctx->current_specifier = (t_conversion_specifier){0};
	ctx->current_specifier.cursor = str;
	parse_flags(ctx);
	if (!parse_width(ctx) || !parse_precision(ctx))
	{
		return (false);
	}
	parse_length(ctx);
	return (true);
}
