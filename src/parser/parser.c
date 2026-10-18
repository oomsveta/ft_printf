/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:04:14 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/18 15:41:58 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>

bool	parse_int(t_ctx *ctx, int *res)
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
	ctx->current_specifier.type = *ctx->current_specifier.cursor;
	return (true);
}
