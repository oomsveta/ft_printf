/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internals.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:39:58 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/18 15:32:30 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct s_flag
{
	bool	left_justify : 1;		// '-' flag
	bool	force_sign : 1;			// '+' flag
	bool	reserve_sign_space : 1;	// ' ' flag
	bool	pad_with_zeros : 1;		// '0' flag
	bool	alternate_form : 1;		// '#' flag
}	t_flags;

#define IGNORED_FLAGS "I'"

typedef struct s_conversion_specifier
{
	int				width;
	int				precision;
	// needed to distinguish no precision set from precision set to 0
	bool			has_precision : 1;
	char			type;
	t_flags			flags;
	const char		*cursor;
}	t_conversion_specifier;

#define PRINTF_BUFFER_SIZE 4096

typedef struct s_buffer
{
	char	data[PRINTF_BUFFER_SIZE];
	size_t	length;
}	t_buffer;

typedef enum e_error
{
	SUCCESS = 0,
	ERR_INT_OVERFLOW,
	ERR_PRECISION_OVERFLOW,
	ERR_WRITE_FAILURE,
}	t_error;

typedef struct s_ctx
{
	t_buffer				buffer;
	size_t					total_written;
	t_error					errno;
	va_list					args;
	t_conversion_specifier	current_specifier;
}	t_ctx;

bool	parse_conversion_specifier(t_ctx *ctx, const char *str);
void	parse_flags(t_ctx *ctx);
bool	parse_width(t_ctx *ctx);
bool	parse_precision(t_ctx *ctx);
void	parse_length(t_ctx *ctx);
