/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:18:06 by mvuente           #+#    #+#             */
/*   Updated: 2020/05/27 13:01:33 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

void		ft_bzero(void *c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *x);
int			ft_tolower(int c);
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_isalnum(int c);
char		*ft_strdup(char const *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *c, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *c, int fd);
int			ft_atoi(const char *ptr);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int a);
int			ft_isdigit(int x);

#endif
