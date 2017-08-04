# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/23 12:31:27 by cchaumar          #+#    #+#              #
#    Updated: 2017/07/13 07:24:13 by cchaumar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLG   = -Wextra -Wall -Werror -g

ifeq ($(ASAN),1)
	CFLG += -fsanitize=address
endif
ifeq ($(FAST),1)
	CFLG += -Ofast
endif

FILES  = load.c write.c
SRCD   = srcs/
OBJD   = objs/
SRCS   = $(addprefix $(SRCD),$(FILES))
OBJS   = $(addprefix $(OBJD),$(FILES:.c=.o))
INCD   = includes/
GENERIC= ../
LIBFT  = ../generics/includes/
HEADERS= bmp.h structs.h
HEAD   = $(addprefix $(HEADERS), $(INCD))
INC    = -I$(INCD) -I$(GENERIC) -I$(LIBFT)

.PHONY : all clean

all : obj $(OBJS)

obj:
	@mkdir -p $(OBJD)

$(OBJD)%.o: $(SRCD)%.c
	gcc $(CFLG) $(INC) -c -o $@ $<

clean:
		@rm -f $(OBJS)
		@echo "printf objects cleaned"

re: clean all
