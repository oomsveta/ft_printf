/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 20:10:58 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 21:20:57 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <limits.h>
#include <stdarg.h>

/**
 * C23 7.23.6.1/6:
 * ---------------
 * For x (or X) conversion, a nonzero result has 0x (or 0X) prefixed to it.
 */
static const char	*get_prefix(const t_conversion_specifier *spec,
	unsigned int n)
{
	if (!spec->flags.alternate_form || n == 0)
	{
		return ("");
	}
	if (spec->type == 'X')
	{
		return ("0X");
	}
	return ("0x");
}

void	put_hex(t_ctx *ctx)
{
	const unsigned int				n = va_arg(ctx->args, unsigned int);
	const t_conversion_specifier	*spec = &ctx->current_specifier;
	char							digits[(sizeof(unsigned int) * CHAR_BIT + 3) / 4 + 1];

	if (n == 0 && spec->has_precision && spec->precision == 0)
	{
		digits[0] = '\0';
	}
	else
	{
		ft_jutoa(n, digits, 16);
	}
	if (spec->type == 'X')
	{
		ft_strupr(digits);
	}
	put_numeric(ctx, digits, get_prefix(spec, n));
}
