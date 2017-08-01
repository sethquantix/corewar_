# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/23 12:31:27 by cchaumar          #+#    #+#              #
#    Updated: 2017/07/13 07:23:28 by cchaumar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLG   = -Wextra -Wall -Werror -g

ifeq ($(ASAN),1)
	CFLG += -fsanitize=address
endif

ifeq ($(FAST),1)
	CFLG += -Ofast
endif

FILES  = quat.c vect.c mat.c quat_op.c vect_op.c
SRCD   = srcs/
OBJD   = objs/
SRCS   = $(addprefix $(SRCD),$(FILES))
OBJS   = $(addprefix $(OBJD),$(FILES:.c=.o))
INCD   = includes/
LIBFT  = ../
GENERIC= ../generics/includes/
HEADERS= math3d.h
HEAD   = $(addprefix $(HEADERS), $(INCD))
INC    = -I$(INCD) -I$(GENERIC) -I$(LIBFT)

.PHONY : all clean

all : $(OBJS)

$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p objs
	gcc $(CFLG) $(INC) -c -o $@ $<

clean:
		@rm -f $(OBJS)
		@echo "printf objects cleaned"

re: clean all
