/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwicket <lwicket@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 22:01:27 by lwicket           #+#    #+#             */
/*   Updated: 2026/10/18 15:12:37 by lwicket          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdint.h>

# if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#  include <windows.h>

# endif

# include <stddef.h>
# include <stdint.h>

# ifdef __GNUC__

typedef uintptr_t __attribute__(\
(__may_alias__, __aligned__ (1)))					t_word;
typedef uintptr_t __attribute__(\
(__may_alias__, __aligned__ (sizeof(uintptr_t))))	t_aligned_word;

# else

typedef unsigned char							t_word;
typedef unsigned char							t_aligned_word;

# endif

int				ft_isupper(int c);
int				ft_islower(int c);
char			*ft_stpcpy(char *dest, const char *src);
char			*ft_stpncpy(char *restrict dest, const char *restrict src, size_t n);
char			*ft_strcpy(char *restrict dest, const char *restrict src);
char			*ft_strchr(const char *str, int chr);
char			*ft_strchrnul(const char *str, int chr);
char			*ft_strdup(const char *str);
char			*ft_strnstr(const char *big, const char *little, size_t n);
char			*ft_strrchr(const char *str, int chr);
char			*ft_strlwr(char *str);
char			*ft_strupr(char *str);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isblank(int c);
int				ft_iscntrl(int c);
int				ft_isdigit(int c);
int				ft_isgraph(int c);
int				ft_isprint(int c);
int				ft_ispunct(int c);
int				ft_isxdigit(int c);
void			*ft_malloc(void *dest, size_t size);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_tolower(int c);
int				ft_toupper(int c);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlen(const char *str);
size_t			ft_strnlen(const char *str, size_t n);
size_t			ft_strspn(const char *str, const char *spn);
void			*ft_calloc(size_t nbr_of_elements, size_t element_size);
void			*ft_memchr(const void *mem, int chr, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *buffer, int byte, size_t size);
void			ft_bzero(void *buffer, size_t size);
size_t          ft_zmin(size_t a, size_t b);
unsigned int	ft_abs(int n);
int				ft_digittoint(int c);

#endif /* LIBFT_H */
