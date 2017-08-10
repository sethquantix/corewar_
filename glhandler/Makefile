# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/23 12:31:27 by cchaumar          #+#    #+#              #
#    Updated: 2017/08/10 05:36:19 by cchaumar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = libglhandler.a
CFLG   :=  -Wextra -Wall -Werror -g

ifeq ($(ASAN),1)
	CFLG += -fsanitize=address
endif

FILES  = gl_objects.c gl_math3d.c gl_shader.c
SRCD   = srcs/
OBJD   = objs/
GITLIB = 'https://github.com\/sethquantix/libft.git'
SRCS   = $(addprefix $(SRCD),$(FILES))
OBJS   = $(addprefix $(OBJD),$(FILES:.c=.o))
FROPEN = -framework OpenGL -framework OpenCL
FRMCOS = -framework Appkit
LIBD   = ..
LIBFT  = $(LIBD)/libft
FRAMEWORKS = $(FROPEN) $(FRMCOS)
INCD   = -Iincludes -I$(LIBFT) -I$(HOME)/.brew/include

all : $(NAME)

$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p objs
	gcc $(CFLG) $(INCD) -c -o $@ $<

$(LIBFT)/libft.a:
	make -C $(LIBFT)

$(NAME): $(LIBFT)/libft.a $(OBJS)
		ar rc $@ $(OBJS)
		ranlib $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all
