/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 15:38:54 by lwicket           #+#    #+#             */
/*   Updated: 2026/11/02 21:30:19 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internals.h"
#include "libft.h"
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>

void	parse_flags(t_ctx *ctx)
{
	t_flags		flags;
	const char	*str = ctx->current_spec.cursor;

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
	ctx->current_spec.flags = flags;
	ctx->current_spec.cursor = str;
}
