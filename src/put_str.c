/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 20:47:40 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 20:50:10 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <stdarg.h>
#include <stddef.h>

void	put_str(t_ctx *ctx)
{
	const t_conversion_specifier	*spec = &ctx->current_specifier;
	const char						*str = va_arg(ctx->args, const char *);
	size_t							len;

	if (str == NULL)
	{
		str = "(null)";
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
