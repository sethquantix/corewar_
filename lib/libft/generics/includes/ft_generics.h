/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 07:06:30 by cchaumar          #+#    #+#             */
/*   Updated: 2017/07/19 09:06:53 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GENERICS_H
# define FT_GENERICS_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <fcntl.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_tree
{
	void			*content;
	size_t			size;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

typedef struct	s_circular
{
	void				*content;
	size_t				size;
	struct s_circular	*next;
	struct s_circular	*prev;
}				t_circular;

typedef struct	s_ft_arr
{
	void		*t;
	size_t		size;
	int			n;
}				t_ft_arr;

typedef int		(*t_ft_cmp)(void *, void *);

t_ft_arr		ft_array(void *t, size_t size, int n);
void			*ft_arr_find(t_ft_arr t, void *ref, int (*f)(void *r, void *c));
char			*acol(int r, int g, int b);
int				ft_atoi_base(const char *str, const char *base);
int				ft_byte(int bit);
unsigned int	ft_endian_int(unsigned int x);
void			ft_endian(void *p, int size);
unsigned char	ft_swap_bits(unsigned char x);
int				ft_isinside(int c, int low, int high);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_islower(int c);
int				ft_isprint(int c);
int				ft_isupper(int c);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *s, char c, size_t len);
void			ft_pushback(void **data, size_t size, int count, void *o);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *s1);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
size_t			ft_tabsize(char **s);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *s1, const char *s2);
void			ft_strtolower(char *s);
void			ft_strtoupper(char *s);
int				ft_tolower(int c);
int				ft_toupper(int c);
void			*ft_memalloc(size_t size);
void			ft_bzero(void *s, size_t n);
void			ft_memdel(void **ap);
void			ft_deltab(char **tab);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoinfree(char const *s1, char const *s2, int mask);
char			*ft_read_file(char *name);
int				ft_iswhite(char c);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_itoa_binary(int n, int base);
void			ft_itoa_buff(char *str, int n);
void			ft_print_bits(size_t const size, void const *const ptr);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr(const char *s);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
int				ft_atoi(char *str);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
t_list			*ft_lstfind(t_list *root, void *data, int (*f)(void *c,
	void *data));
t_list			*ft_lst_filter(t_list *root, int (*f)(void *content));
void			*ft_lst_flat(t_list *root, void *(*f)(int i, void *p), size_t
	elem_size);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstend(t_list *ls);
void			ft_lstadd(t_list **alst, t_list *node);
void			ft_lstadd_end(t_list **alst, t_list *node);
size_t			ft_lstsize(t_list *root);
void			ft_lst_remove_if(t_list **list, void *ref,
	int (*f)(void *reference, void *content),
	void (*del)(void *content, size_t size));
t_circular		*ft_circular_new(void *content, size_t size);
t_circular		*ft_circular_add_tail(t_circular **head, t_circular *node);
t_circular		*ft_circular_add_head(t_circular **head, t_circular *node);
t_circular		*ft_circular_find(t_circular *head, void *data,
	int (*f)(void *, void *));
int				ft_circ_find_ind(t_circular *head, void *data,
	int (*f)(void *, void *));
int				ft_circ_equal(void *node, void *data);
void			*run_circular(t_circular *head, void *data,
	void *(*f)(void *, void *, size_t));
void			ft_circular_delete_node(t_circular **head, t_circular *old);
void			ft_circular_free(t_circular **head);
void			ft_dummy(void *content, size_t size);
void			ft_del(void *ptr, size_t size);
void			ft_lst_delif(t_list **root, t_list *node);
int				get_next_line(int const fd, char **line);
void			*try(size_t size);
char			*ft_read_file(char *name);
char			*ft_trim(char **s);
t_tree			*ft_tree_new(void *content, size_t size);
t_tree			*ft_tree_insert(t_tree **root, t_tree *node,
	int (*f)(void *, void *));
t_tree			*ft_tree_find(t_tree *root, void *ref,
	int (*cmp)(void *, void *));
void			ft_tree_del(t_tree **root,
	void (*del)(void *content, size_t size));

#endif
