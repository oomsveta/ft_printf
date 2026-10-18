/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 15:38:57 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/18 15:40:21 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>

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
