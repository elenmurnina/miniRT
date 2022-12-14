/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 16:56:02 by hregina           #+#    #+#             */
/*   Updated: 2021/09/19 16:56:04 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include "../get_next_line/get_next_line.h"

void	*ft_memset(void *destination, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *destination, const void *source, size_t n);
void	*ft_memccpy(void *destination, const void *source, int c, size_t n);
void	*ft_memmove(void *destination, const void *source, size_t n);
void	*ft_memchr(const void *arr, int c, size_t n);
int		ft_memcmp(const void *arr1, const void *arr2, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *destination, const char *source, size_t n);
size_t	ft_strlcat(char *destination, const char *source, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strrchr(const char *str, int c);
char	*ft_strnstr(const char *str, const char *find, size_t n);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_calloc(size_t n, size_t size);
char	*ft_strdup(const char *source);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_reverse(char *str);
char	**ft_split(char const *s, char c);
double	ft_atod(const char *str);
char	*ft_itoa(int n);
char	*ft_utoa(unsigned int n);
char	*ft_xtoa(unsigned int n);
char	*ft_ptoa(void *p);
char	*ft_otoa(unsigned int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_min_int(int first, int second);
int		ft_max_int(int first, int second);
void	ft_swap(char *dest, char *src);
int		ft_abs(int j);
void	ft_dyn_arr_free_char(char **arr, int row);
void	ft_dyn_arr_free_int(int **arr, int row);
char	**ft_dyn_arr_mal_char(int row, int col);
int		**ft_dyn_arr_mal_int(int row, int col);
void	ft_free_split(char	**tmp);

#endif
