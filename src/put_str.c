/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 20:47:40 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 21:09:14 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <stdarg.h>
#include <stddef.h>

void	put_str(t_ctx *ctx)
{
	t_conversion_specifier	*spec;
	const char				*str = va_arg(ctx->args, const char *);
	size_t					len;

	spec = &ctx->current_specifier;
	spec->flags.pad_with_zeros = false;
	if (str == NULL)
	{
		str = "(null)";
		if (spec->has_precision && (size_t)spec->precision < ft_strlen(str))
		{
			str = "";
		}
	}
	if (spec->has_precision)
	{
		len = ft_strnlen(str, (size_t)spec->precision);
	}
	else
	{
		len = ft_strlen(str);
	}
	put_padded(ctx, str, len);
}
