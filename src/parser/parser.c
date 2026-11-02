/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:04:14 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 22:15:33 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * @brief Parses a positive number from the current cursor position.
 * 
 * Advances the cursor as it parses and stores the successfully parsed result in
 * the int pointed to by @p res.
 *
 * In case of integer overflow, @p res is set to @c INT_MIN, context's error is
 * set to @c ERR_INT_OVERFLOW, and the function returns false.
 * 
 * @param ctx Pointer to the context.
 * @param res Pointer to an integer where the result will be stored.
 * @return true if the integer was parsed successfully, or false if an overflow
 *         occurred.
 *
 * @warning Only handles positive numbers. Tailored for use in parse_width() and
 *          parse_precision(). Do NOT use as a general-purpose parser.
 */
bool	parse_int(t_ctx *ctx, int *res)
{
	int			acc;
	int			digit;
	const char	*nptr = ctx->current_spec.cursor;
	const int	cutoff = INT_MAX / 10;
	const int	cutlim = INT_MAX % 10;

	acc = 0;
	while (ft_isdigit(*nptr))
	{
		digit = ft_digittoint(*nptr);
		if (acc > cutoff || (acc == cutoff && digit > cutlim))
		{
			ctx->error = ERR_INT_OVERFLOW;
			*res = INT_MIN;
			return (false);
		}
		acc = acc * 10 + digit;
		nptr += 1;
	}
	ctx->current_spec.cursor = nptr;
	*res = acc;
	return (true);
}

/**
 * @brief Parses a conversion spec from the provided @p str.
 *
 * Fills context's @c current_spec with the parsed data.
 *
 * @param ctx Pointer to the context.
 * @param str Pointer to the start of the spec to parse (i.e., what comes
 8            right after the '%' in a printf format string).
 * @return true if parsing succeeds, or false if parsing fails and the printf
 *         call must abort.
 */
bool	parse_conversion_specification(t_ctx *ctx, const char *str)
{
	ctx->current_spec = (t_spec){0};
	ctx->current_spec.cursor = str;
	parse_flags(ctx);
	if (!parse_width(ctx) || !parse_precision(ctx))
	{
		return (false);
	}
	parse_length(ctx);
	ctx->current_spec.type = *ctx->current_spec.cursor;
	ctx->current_spec.cursor += *ctx->current_spec.cursor != '\0';
	return (true);
}
