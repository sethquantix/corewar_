CFLG := -Wextra -Wall -Werror -g

ifeq ($(ASAN),1)
	CFLG += -fsanitize=address
endif

ifeq ($(FAST),1)
	CFLG += -Ofast
endif

FILES= 	ft_arr_find.c \
		ft_atoi.c \
		ft_atoi_base.c \
		ft_itoa_buff.c \
		ft_byte.c \
		ft_bzero.c \
		ft_circular_find.c \
		ft_circular_funcs.c \
		ft_color.c \
		ft_del.c \
		ft_deltab.c \
		ft_dummy.c \
		ft_endian.c \
		ft_endian_int.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isinside.c \
		ft_islower.c \
		ft_isprint.c \
		ft_isupper.c \
		ft_iswhite.c \
		ft_itoa.c \
		ft_itoa_binary.c \
		ft_lstadd.c \
		ft_lstadd_end.c \
		ft_lstdel.c \
		ft_lst_delif.c \
		ft_lstdelone.c \
		ft_lstend.c \
		ft_lstfind.c \
		ft_lst_flat.c \
		ft_lst_filter.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lst_remove_if.c \
		ft_lstsize.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_pushback.c \
		ft_print_bits.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_read_file.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strjoinfree.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strndup.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtolower.c \
		ft_strtoupper.c \
		ft_strtrim.c \
		ft_swap_bits.c \
		ft_tabsize.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_tree.c \
		ft_trim.c \
		ft_try.c \
		get_next_line.c \

OBJD = objs/
SRCD = srcs/
SRCS = $(addprefix $(SRCD), $(FILES))
OBJS = $(addprefix $(OBJD), $(FILES:.c=.o))
HDRS = ft_generics.h get_next_line.h
INCD = includes/
HEAD = $(addprefix $(INCD), $(HDRS))
INC  = -I$(INCD)
CC   = gcc

all : obj $(OBJS)

obj:
	@mkdir -p $(OBJD)

$(OBJD)%.o: $(SRCD)%.c ${HEAD}
		$(CC) $(CFLG) $(INC) -c -o $@ $<

clean:
		@rm -f $(OBJS)
		@echo "objects cleaned"

re: clean $(OBJS)
