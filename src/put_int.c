/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 16:33:22 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 20:23:09 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <limits.h>
#include <stdarg.h>

static inline const char	*get_prefix(t_flags flags, int n)
{
	if (n < 0)
	{
		return ("-");
	}
	if (flags.force_sign)
	{
		return ("+");
	}
	if (flags.reserve_sign_space)
	{
		return (" ");
	}
	return ("");
}

void	put_int(t_ctx *ctx)
{
	const int						n = va_arg(ctx->args, int);
	char							buffer[sizeof(int) * CHAR_BIT + 1];
	const t_conversion_specifier	*spec = &ctx->current_specifier;

	if (n == 0 && spec->has_precision && spec->precision == 0)
	{
		buffer[0] = '\0';
	}
	else
	{
		ft_jutoa(ft_abs(n), buffer, 10);
	}
	put_numeric(ctx, buffer, get_prefix(spec->flags, n));
}
