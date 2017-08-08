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
CFLG   = -Wall -Wextra -Werror -g
THIS   = Makefile

CRWRF  =	utils/op.c \
			corewar.c \
            utils/utils.c \
            graphics/gr_gen_tex.c \
            graphics/gr_gl_init_vbos.c \
            graphics/gr_gl_update.c \
            graphics/gr_vm_camera_handling.c \
            graphics/gr_vm_camera_handling_rot.c \
            graphics/gr_vm_clear.c \
            graphics/gr_vm_gl.c \
            graphics/gr_vm_handlers.c \
            graphics/gr_vm_init.c \
            graphics/gr_vm_init_cube.c \
            graphics/gr_vm_inputs.c \
            graphics/gr_vm_keys.c \
            graphics/gr_vm_matrix.c \
            graphics/gr_vm_render_opengl.c \
            graphics/gr_vm_run.c \
            graphics/gr_vm_selector.c \
            graphics/gr_vm_styles.c \
            graphics/gr_vm_ui.c \
            graphics/gr_vm_ui_utils.c \
            core/parser/options.c \
            core/parser/options2.c \
            core/parser/opts_tokens.c \
            core/parser/parse_args.c \
            core/parser/read_args.c \
            core/memory/mem.c \
            core/memory/values.c \
            core/instructions/ins_basic.c \
            core/instructions/ins_calc.c \
            core/instructions/ins_fork.c \
            core/instructions/ins_index.c \
            core/instructions/process.c \
            core/instructions/process_read.c \
            core/init/arena_ini.c \
            core/init/check_process.c

ASMF   =    asm.c \
            asm_tokens.c \
            color.c \
			file.c \
            compile.c \
            inst_tools.c \
            labels_tools.c \
            more_utils.c \
            op.c \
            opt_tokens.c \
            params_tools.c \
            parse_asm.c \
            parse_opts.c \
            print.c \
            print_instruction.c \
            read_opts.c \
            utils.c \
            write.c \
            decompile/dec_err_check.c \
            decompile/dec_lst_op.c \
            decompile/decompile.c \
            decompile/set_check_labels.c \
            decompile/set_op.c \
            decompile/set_params.c \
            decompile/write_head.c \
            decompile/write_ops.c
SRCD   = srcs
OBJD   = objs
BINC   = $(HOME)/.brew/include
BLIB   = $(HOME)/.brew/lib
CRWRSD = $(SRCD)/corewar_srcs/
ASMSD  = $(SRCD)/asm_srcs/
CRWROD = $(OBJD)/corewar_objs/
ASMOD  = $(OBJD)/asm_objs/
LIBFT  = lib/libft/libft.a
LIBGL  = lib/glhandler/libglhandler.a
SOIL2  = lib/soil2/libSOIL2.a
ALIBS  = -Llib/libft -lft
CLIBS  = -Llib/libft -lft -Llib/glhandler -lglhandler -Llib/soil2 \
		 -L$(BLIB) -lglew -lSDL2 -lSOIL2 -lSDL2_ttf -framework OpenGL
CRWRS  = $(addprefix $(CRWRSD), $(CRWRF))
CRWRO  = $(addprefix $(CRWROD), $(CRWRF:.c=.o))
ASMS   = $(addprefix $(ASMSD), $(ASMF))
ASMO   = $(addprefix $(ASMOD), $(ASMF:.c=.o))
ASMH   = includes/asm/asm.h includes/asm/decompile.h includes/op.h
OBJDIR =    $(OBJD) \
            $(OBJD)/corewar_objs \
            $(OBJD)/corewar_objs/utils \
            $(OBJD)/corewar_objs/core \
            $(OBJD)/corewar_objs/core/init \
            $(OBJD)/corewar_objs/core/instructions \
            $(OBJD)/corewar_objs/core/memory \
            $(OBJD)/corewar_objs/core/parser \
            $(OBJD)/corewar_objs/graphics \
            $(OBJD)/asm_objs/ \
            $(OBJD)/asm_objs/decompile

CRWRH  =    includes/corewar/corewar.h \
            includes/corewar/includes.h \
            includes/corewar/internals/crwr_defines.h \
            includes/corewar/internals/crwr_globals.h \
            includes/corewar/internals/crwr_structs.h \
            includes/corewar/internals/crwr_types.h \
            includes/corewar/graphics/gr_structs.h \
            includes/corewar/graphics/gr_types.h \
            includes/corewar/graphics/gr_vm.h \
            includes/corewar/graphics/gr_vm_internals.h \
            includes/corewar/graphics/styles.h \
            includes/op.h
CRINC   = -Iincludes -Iincludes/corewar -Iincludes/corewar/graphics \
		  -Iincludes/internals \
		  -Ilib/libft -Ilib/glhandler/includes -Ilib/soil2/incs -I$(BINC)
ASMINC  = -Iincludes -Iincludes/asm -Ilib/libft
OBJS   = $(CRWRO) $(ASMO)

.PHONY: lib all clean re fclean libft glhandler update

all : $(CRWR) $(ASM)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

lib/soil2/libSOIL2.a:
	@make -C lib/soil2/

lib/libft/libft.a:
	@make -C lib/libft

lib/glhandler/libglhandler.a:
	@make -C lib/glhandler

$(CRWROD)%.o: $(CRWRSD)%.c ${CRWRH} ${THIS}
	gcc $(CFLG) $(CRINC) -c -o $@ $<

$(ASMOD)%.o: $(ASMSD)%.c ${ASMH} ${THIS}
	gcc $(CFLG) $(ASMINC) -c -o $@ $<

$(CRWR): $(OBJDIR) $(CRWRO) $(LIBFT) $(LIBGL) $(SOIL2)
		gcc $(CFLG) $(INC) $(CLIBS) -o $@ $(CRWRO)

$(ASM): $(OBJDIR) $(ASMO) $(LIBFT)
		gcc $(CFLG) $(INC) $(ALIBS) -o $@ $(ASMO)

clean:
		@rm -f $(OBJS)
		@echo "Objects cleaned."

fclean: clean
		@rm -f $(CRWR) $(ASM)
		@echo "Binaries cleaned."

re: fclean all
