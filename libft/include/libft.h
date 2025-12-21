/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:39:57 by username          #+#    #+#             */
/*   Updated: 2025/11/15 14:33:07 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef SIZE_MAX
#  define SIZE_MAX 18446744073709551615ul
# endif

int32_t				ft_isalpha(int32_t c);
int32_t				ft_isdigit(int32_t c);
int32_t				ft_isalnum(int32_t c);
int32_t				ft_isascii(int32_t c);
int32_t				ft_isprint(int32_t c);
int					ft_isspace(int c);

size_t				ft_strlen(const char *s);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, void *src, size_t n);
size_t				ft_strlcpy(char *dest, char *src, size_t n);
size_t				ft_strlcat(char *dest, char *src, size_t n);

int32_t				ft_toupper(int32_t c);
int32_t				ft_tolower(int32_t c);

char				*ft_strchr(const char *s, int32_t c);
char				*ft_strrchr(const char *s, int32_t c);
int32_t				ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(void *s, int32_t c, size_t n);
int32_t				ft_memcmp(void *s1, void *s2, size_t n);
char				*ft_strnstr(char *str, char *to_find, size_t n);

void				*ft_calloc(size_t n, size_t n_bytes);
char				*ft_strdup(char *s);
char				*ft_substr(char const *s, uint32_t start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
void				free_split(char **s);

int32_t				ft_atoi(const char *nptr);
int64_t				ft_atol(const char *nptr);
char				*ft_itoa(int32_t n);
char				*ft_utoa(uint32_t n);
char				*ft_ltoa(int64_t n);
char				*ft_lutoa(uint64_t n);

char				*ft_strmapi(char const *s, char (*f)(uint32_t, char));
void				ft_striteri(char *s, void (*f)(uint32_t, char *));

void				ft_putchar_fd(char c, int32_t fd);
void				ft_putstr_fd(char *s, int32_t fd);
void				ft_putendl_fd(char *s, int32_t fd);
void				ft_putnbr_fd(int32_t n, int32_t fd);

char				*ft_strcpy(char *dst, char *src);

int32_t				ft_absi(int32_t n);
int64_t				ft_absl(int64_t n);
int32_t				ft_mini32(int32_t a, int32_t b);
uint32_t			ft_minu32(uint32_t a, uint32_t b);
int64_t				ft_mini64(int64_t a, int64_t b);
uint64_t			ft_minu64(uint64_t a, uint64_t b);
int32_t				ft_maxi32(int32_t a, int32_t b);
uint32_t			ft_maxu32(uint32_t a, uint32_t b);
int64_t				ft_maxi64(int64_t a, int64_t b);
uint64_t			ft_maxu64(uint64_t a, uint64_t b);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int32_t				ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
