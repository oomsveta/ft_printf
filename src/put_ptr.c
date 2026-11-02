/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:30:00 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 21:13:25 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>

static const char	*get_prefix(t_flags flags)
{
	if (flags.force_sign)
	{
		return ("+0x");
	}
	if (flags.reserve_sign_space)
	{
		return (" 0x");
	}
	return ("0x");
}

void	put_ptr(t_ctx *ctx)
{
	const uintptr_t		ptr = (uintptr_t)va_arg(ctx->args, void *);
	t_flags				*flags;
	char				digits[(sizeof(uintptr_t) * CHAR_BIT + 3) / 4 + 1];

	flags = &ctx->current_specifier.flags;
	if (ptr == 0)
	{
		flags->pad_with_zeros = false;
		put_padded(ctx, "(nil)", 5);
		return ;
	}
	ft_jutoa(ptr, digits, 16);
	put_numeric(ctx, digits, get_prefix(*flags));
}
