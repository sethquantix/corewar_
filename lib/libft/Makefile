# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/01 03:54:10 by cchaumar          #+#    #+#              #
#    Updated: 2017/07/20 01:05:46 by cchaumar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = libft.a

CC       = gcc
FLAGS    = -Wall -Wextra -Werror -g
THIS     = Makefile

ifeq ($(ASAN),1)
	FLAGS += -fsanitize=address
endif

ifeq ($(FAST),1)
	FLAGS += -Ofast
endif

GEN_F    =	ft_atoi.c				ft_byte.c				ft_bzero.c \
			ft_circular_find.c		ft_circular_funcs.c		ft_del.c \
			ft_deltab.c				ft_dummy.c				ft_endian.c \
			ft_endian_int.c			ft_isalnum.c			ft_isalpha.c \
			ft_isascii.c			ft_isdigit.c			ft_isinside.c \
			ft_islower.c			ft_isprint.c			ft_isupper.c \
			ft_iswhite.c			ft_itoa.c				ft_itoa_binary.c \
			ft_lstadd.c				ft_lstadd_end.c			ft_lstdel.c \
			ft_lst_delif.c			ft_lstdelone.c			ft_lstfind.c \
			ft_lst_flat.c			ft_lst_filter.c			ft_lstiter.c \
			ft_lstmap.c				ft_lstnew.c				ft_lst_remove_if.c \
			ft_lstsize.c			ft_memalloc.c			ft_memccpy.c \
			ft_memchr.c				ft_memcmp.c				ft_memcpy.c \
			ft_memdel.c				ft_memmove.c			ft_memset.c \
			ft_print_bits.c			ft_putchar.c			ft_putchar_fd.c \
			ft_putendl.c			ft_putendl_fd.c			ft_putnbr.c \
			ft_putnbr_fd.c			ft_putstr.c				ft_putstr_fd.c \
			ft_strcat.c 			ft_strchr.c				ft_strclr.c \
			ft_strcmp.c				ft_strcpy.c				ft_strdel.c \
			ft_strdup.c				ft_strequ.c				ft_striter.c \
			ft_striteri.c			ft_strjoin.c			ft_strjoinfree.c \
			ft_strlcat.c			ft_strlen.c				ft_strmap.c \
			ft_strmapi.c			ft_strncat.c			ft_strncmp.c \
			ft_strncpy.c			ft_strndup.c			ft_strnequ.c \
			ft_strnew.c				ft_strnstr.c			ft_strrchr.c \
			ft_strsplit.c			ft_strstr.c				ft_strsub.c \
			ft_strtolower.c			ft_strtoupper.c			ft_strtrim.c \
			ft_swap_bits.c 			ft_tabsize.c			ft_tolower.c \
			ft_toupper.c			get_next_line.c			ft_trim.c \
			ft_try.c				ft_read_file.c			ft_pushback.c \
			ft_atoi_base.c			ft_arr_find.c			ft_lstend.c \
			ft_color.c				ft_itoa_buff.c			ft_tree.c \

PRF_F    =	printf.c		funcs.c			parse.c			output.c \
			casts.c			get.c 			itoa64.c		wchar.c \
			casts2.c 		terminate.c		dprintf.c
BMP_F    =	load.c			write.c
PRSR_F	 =	parser.c		build_engine.c	opts.c			evals.c \
			engine_run.c	check_tokens.c	expr.c			run_paths.c \
			utils.c 		parser_destroy.c \

MATH_F   =	quat.c			vect.c			mat.c			quat_op.c \
			vect_op.c
OCL_F    =	ft_opencl.c		kernel.c		devices.c		run.c

GEN_SD   = generics/srcs/
GEN_OD   = generics/objs/
GEN_INC  = -Igenerics/includes

GEN_H	 = generics/includes/ft_generics.h \
		   generics/includes/get_next_line.h \

PRF_SD   = printf/srcs/
PRF_OD   = printf/objs/
PRF_INC  = -Iprintf/includes -Igenerics/includes

PRF_H    = printf/includes/defines.h \
		   printf/includes/parse.h \
		   printf/includes/printf.h \

BMP_SD   = bmp/srcs/
BMP_OD   = bmp/objs/
BMP_INC  = -Ibmp/includes

BMP_H     = bmp/includes/bmp.h \
			bmp/includes/structs.h \

PRSR_SD   = parser/srcs/
PRSR_OD   = parser/objs/
PRSR_INC  = -Iparser/includes -Igenerics/includes

PRSR_H    = parser/includes/build.h \
			parser/includes/ft_parser.h \
			parser/includes/parser.h \
			parser/includes/parser_marching.h \

MATH_SD   = math/srcs/
MATH_OD   = math/objs/
MATH_INC  = -Imath/includes

MATH_H    = math/includes/math3d.h \

OCL_SD    = opencl/srcs/
OCL_OD    = opencl/objs/
OCL_INC   = -Iopencl/includes

OCL_H     = opencl/includes/ft_opencl.h \

GEN_S    = $(addprefix $(GEN_SD), $(GEN_F))
GEN_O    = $(addprefix $(GEN_OD), $(GEN_F:.c=.o))
PRF_S    = $(addprefix $(PRF_SD), $(PRF_F))
PRF_O    = $(addprefix $(PRF_OD), $(PRF_F:.c=.o))
PRSR_S   = $(addprefix $(PRSR_SD), $(PRSR_F))
PRSR_O   = $(addprefix $(PRSR_OD), $(PRSR_F:.c=.o))
BMP_S    = $(addprefix $(BMP_SD), $(BMP_F))
BMP_O    = $(addprefix $(BMP_OD), $(BMP_F:.c=.o))
MATH_S    = $(addprefix $(MATH_SD), $(MATH_F))
MATH_O    = $(addprefix $(MATH_OD), $(MATH_F:.c=.o))
OCL_S     = $(addprefix $(OCL_SD), $(OCL_F))
OCL_O     = $(addprefix $(OCL_OD), $(OCL_F:.c=.o))
SRCS     = $(GEN_S) $(PRF_S) $(BMP_S) $(PRSR_S) $(MATH_S) $(OCL_S)
OBJS     = $(GEN_O) $(PRF_O) $(BMP_O) $(PRSR_O) $(MATH_O) $(OCL_O)

.PHONY: printf generic ocl bmp parser math all

all : $(NAME)

$(GEN_OD)%.o: $(GEN_SD)%.c ${GEN_H} ${THIS}
	$(CC) $(FLAGS) $(GEN_INC) -c -o $@ $<

$(PRF_OD)%.o: $(PRF_SD)%.c ${PRF_H} ${THIS}
	$(CC) $(FLAGS) $(PRF_INC) -c -o $@ $<

$(BMP_OD)%.o: $(BMP_SD)%.c ${BMP_H} ${THIS}
	$(CC) $(FLAGS) $(BMP_INC) -c -o $@ $<

$(PRSR_OD)%.o: $(PRSR_SD)%.c ${PRSR_H} ${THIS}
	$(CC) $(FLAGS) $(PRSR_INC) -c -o $@ $<

$(MATH_OD)%.o: $(MATH_SD)%.c ${MATH_H} ${THIS}
	$(CC) $(FLAGS) $(MATH_INC) -c -o $@ $<

$(OCL_OD)%.o: $(OCL_SD)%.c ${OCL_H} ${THIS}
	$(CC) $(FLAGS) $(OCL_INC) -c -o $@ $<

$(NAME): $(OBJS)
		@printf "Linking : "
		@ar rc $@ $(OBJS)
		@printf "Linked.\nOrdering : "
		@ranlib $@
		@printf "Ordered.\nDone !\n"

clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re: fclean all
