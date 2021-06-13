/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:37:47 by yokawada          #+#    #+#             */
/*   Updated: 2021/06/11 03:38:52 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef unsigned long long	t_ull;

void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
size_t			ft_strlen(const char *str);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strchr(const char *s, int c);
int				ft_stri(const char *s, int c);
char			*ft_strchr_nn(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isupper(int c);
int				ft_islower(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
void			ft_strupcase(char *str);
int				ft_tolower(int c);
char			*ft_strdup(const char *src);
void			*ft_calloc(size_t count, size_t size);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_straddcfront(char c, size_t t, const char *s);
char			*ft_strjoin_destroy_both(char **s1, char **s2);
char			*ft_strjoin_destroy2(const char *s1, char **s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *str, char c);
char			*ft_itoa(int n);
char			*ft_uitoa_base(t_ull n, int base, int negative, ssize_t least);
char			*ft_itoa_base(long long n, int base, ssize_t least);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
ssize_t			ft_rputchar_fd(char c, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
ssize_t			ft_rputstr_fd(char *s, int fd);
void			ft_putnstr_fd(char *s, int fd, size_t n);
ssize_t			ft_rputnstr_fd(char *s, int fd, size_t n);
void			ft_putstr_endl_fd(int fd, char *str);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putchar_ntimes_fd(char c, size_t times, int fd);
ssize_t			ft_rputchar_ntimes_fd(char c, size_t times, int fd);

size_t			ft_wstrlen(const wchar_t *wstr);
ssize_t			ft_rputnwstr_fd(wchar_t *s, int fd, size_t n);
char			*ft_wstr2str(const wchar_t *wstr);
void			ft_putwstr_fd(wchar_t *s, int fd);
void			ft_putnwstr_fd(wchar_t *s, int fd, size_t n);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst,
					void *(*f)(void *), void (*del)(void *));

#endif
