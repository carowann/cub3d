/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:52:40 by giomastr          #+#    #+#             */
/*   Updated: 2025/05/09 15:37:24 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <ctype.h>
# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/wait.h>

# define BASE16 16
# define BASE16UP 17
# define BASE10 10
//# define BASE16 "0123456789abcdef"
//# define BASE16UP "0123456789ABCDEF"
//# define BASE10 "0123456789"

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 10
// # endif

// # define MAX_FD 1024

//basic functions
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *nptr);
int		ft_put_ptr(uintptr_t ptr);

//memory functions
void	*ft_memset(void *s, int c, size_t n);
void	*ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);

//string functions
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

//malloc functions
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
char	**ft_split(char const *s, char lim);

//fd functions
int		ft_putstr_fd(const char *s, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_putchar_fd(char c, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_putnbr_base_fd(unsigned int n, unsigned int base, int fd);

//list functions

//printf functions
int		ft_printf(const char *form, ...);
int		format(char c, va_list args);

//gnl functions
void	free_n_null(char **buffer);
char	*get_the_leftovers(char *the_stash);
char	*get_the_line(char *the_stash);
char	*read_the_stuff(int fd, char *the_stash);
char	*get_next_line(int fd);
size_t	gnl_strlen(const char *s);
void	*gnl_calloc(size_t nmemb, size_t size);
char	*gnl_str_add(char *s1, char const *s2);
char	*gnl_strchr(const char *s, int c);
char	*gnl_substr(char const *s, unsigned int start, size_t len);

#endif
