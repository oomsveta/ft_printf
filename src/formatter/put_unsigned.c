/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_unsigned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 22:24:38 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/10 22:41:17 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <limits.h>
#include <stdarg.h>

void	put_unsigned(t_ctx *ctx)
{
	const unsigned int	n = va_arg(ctx->args, unsigned int);
	const t_spec		*spec = &ctx->current_spec;
	char				digits[sizeof(unsigned int) * CHAR_BIT * 28 / 93 + 2];

	if (n == 0 && spec->has_precision && spec->precision == 0)
	{
		digits[0] = '\0';
	}
	else
	{
		ft_jutoa(n, digits, 10);
	}
	put_numeric(ctx, digits, "");
}
