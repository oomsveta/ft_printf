/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:04:14 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/15 19:45:48 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <limits.h>
#include <stdarg.h>

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

static bool	parse_width_from_va_args(t_ctx *ctx)
{
	const int				width = va_arg(ctx->args, int);
	t_conversion_specifier	*specifier;

	specifier = &ctx->current_specifier;
	specifier->width = (int)ft_abs(width);
	if (width < 0)
	{
		specifier->flags.left_justify = true;
		specifier->flags.pad_with_zeros = false;
		if (width == INT_MIN)
		{
			specifier->width = 0;
			ctx->errno = ERR_WIDTH_OVERFLOW;
			return (false);
		}
	}
	return (true);
}

bool	parse_width(t_ctx *ctx)
{
	int			acc;
	int			digit;
	const char	*nptr = ctx->current_specifier.cursor;
	const int	cutoff = INT_MAX / 10;
	const int	cutlim = INT_MAX % 10;

	if (*nptr == '*')
	{
		ctx->current_specifier.cursor += 1;
		return (parse_width_from_va_args(ctx));
	}
	acc = 0;
	while (ft_isdigit(*nptr))
	{
		digit = ft_digittoint(*nptr++);
		if (acc > cutoff || (acc == cutoff && digit > cutlim))
		{
			ctx->errno = ERR_WIDTH_OVERFLOW;
			return (false);
		}
		acc = acc * 10 + digit;
	}
	ctx->current_specifier.cursor = nptr;
	ctx->current_specifier.width = acc;
	return (true);
}

bool	parse_specifier(t_ctx *ctx, const char *str)
{
	ctx->current_specifier = (t_conversion_specifier){0};
	ctx->current_specifier.cursor = str;
	parse_flags(ctx);
	parse_width(ctx);
	return (true);
}
