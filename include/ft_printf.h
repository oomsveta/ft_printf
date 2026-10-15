/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 22:20:37 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/15 19:22:29 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# if defined __has_attribute
#  if __has_attribute(format)
#   define FORMAT_ATTR_SUPPORTED
#  endif
# endif

# if defined FORMAT_ATTR_SUPPORTED

int	ft_printf(const char *format, ...) __attribute__((format(printf, 1, 2)));

# else

int	ft_printf(const char *format, ...);

# endif

#endif /* FT_PRINTF_H */
