# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/23 12:31:27 by lnagy             #+#    #+#              #
#*   Updated: 2016/10/18 17:40:03 by lnagy            ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

CRWR   = corewar
ASM    = asm
CFLG   = -g -fsanitize=address
CRWRF  = corewar.c gr_vm_run.c gr_vm_init.c gr_vm_inputs.c gr_vm_handlers.c \
		 gr_gl_buffer.c utils.c arena_ini.c process.c op.c mem.c \
		 ins_basic.c ins_fork.c ins_index.c ins_calc.c check_process.c \
		 opts_tokens.c parse_args.c gr_vm_init_cube.c gr_vm_render_opengl.c
ASMF   = asm.c opt_tokens.c parse_opts.c utils.c read_opts.c \
		 asm_tokens.c parse_asm.c op.c compile.c write.c print.c 
SRCD   = srcs
OBJD   = objs
BINC   = $(HOME)/.brew/include
BLIB   = $(HOME)/.brew/lib
CRWRSD = $(SRCD)/corewar_srcs/
ASMSD  = $(SRCD)/asm_srcs/
CRWROD = $(OBJD)/corewar_objs/
ASMOD  = $(OBJD)/asm_objs/
LIBFT  = https://www.github.com/sethquantix/libft.git
HANDLER= https://www.github.com/sethquantix/glhandler.git
ALIBS  = -Llibs/libft -lft 
CLIBS  = -Llibs/libft -lft -L$(BLIB) -Llibs/glhandler -lglhandler -lglew -lSDL2 -framework OpenGL
CRWRS  = $(addprefix $(CRWRSD), $(CRWRF))
CRWRO  = $(addprefix $(CRWROD), $(CRWRF:.c=.o))
ASMS   = $(addprefix $(ASMSD), $(ASMF))
ASMO   = $(addprefix $(ASMOD), $(ASMF:.c=.o))
ASMH   = includes/asm.h
CRWRH  = includes/corewar.h
INC    = -Iincludes -Ilibs/libft -I$(BINC)
OBJS   = $(CRWRO) $(ASMO)

.PHONY: lib all clean re fclean libft glhandler update

all : $(CRWR) $(ASM)

libft:
	@if [ -a "libs/libft" ]; \
	then git -C libs/libft pull; \
	else git clone $(LIBFT) libs/libft;\
	fi;
	make -C libs/libft

glhandler:
	@if [ -a "libs/glhandler" ]; \
	then git -C libs/glhandler pull; \
	else git clone $(HANDLER) libs/glhandler;\
	fi;
	make -C libs/glhandler

update: libft glhandler

$(CRWROD)%.o: $(CRWRSD)%.c ${CRWRH}
	gcc $(CFLG) $(INC) -c -o $@ $<

$(ASMOD)%.o: $(ASMSD)%.c ${ASMH}
	gcc $(CFLG) $(INC) -c -o $@ $<

$(CRWR): $(CRWRO)
		gcc $(CFLG) $(INC) $(CLIBS) -o $@ $(CRWRO)

$(ASM): $(ASMO)
		gcc $(CFLG) $(INC) $(ALIBS) -o $@ $(ASMO)

clean:
		@rm -f $(OBJS)
		@echo "Objects cleaned."

fclean: clean
		@rm -f $(CRWR) $(ASM)
		@echo "Binaries cleaned."

re: fclean all
