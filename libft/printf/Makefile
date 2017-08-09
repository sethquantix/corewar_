# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/23 12:31:27 by cchaumar          #+#    #+#              #
#    Updated: 2017/07/13 07:23:51 by cchaumar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLG   := -Wextra -Wall -Werror -g

ifeq ($(ASAN),1)
	CFLG += -fsanitize=address
endif

ifeq ($(FAST),1)
	CFLG += -Ofast
endif

FILES  = printf.c funcs.c parse.c output.c casts.c get.c itoa64.c wchar.c \
		 casts2.c terminate.c dprintf.c
SRCD   = srcs/
OBJD   = objs/
GITLIB = 'https://github.com\/sethquantix/libft.git'
SRCS   = $(addprefix $(SRCD),$(FILES))
OBJS   = $(addprefix $(OBJD),$(FILES:.c=.o))
INCD   = includes/
GENERIC= ../generics/includes/
HEADERS= printf.h defines.h parse.h
HEAD   = $(addprefix $(HEADERS), $(INCD))
INC    = -I$(INCD) -I$(GENERIC)

.PHONY : all clean

all : $(OBJS)

$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p objs
	gcc $(CFLG) $(INC) -c -o $@ $<

clean:
		@rm -f $(OBJS)
		@echo "printf objects cleaned"

re: clean all
