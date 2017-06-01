cmake_minimum_required(VERSION 3.5)
project(_corewar)

set(CMAKE_CXX_STANDARD 11)

SET(GCC_OPTIONS "-g -fsanitize=address -v")

include_directories(includes
		soil2/incs
        libs/libft)

set(CRWR_FILES
    includes/corewar.h
    includes/crwr_defines.h
    includes/crwr_globals.h
    includes/crwr_structs.h
    includes/crwr_types.h
    includes/gr_structs.h
    includes/gr_types.h
    includes/gr_vm.h
    includes/gr_vm_internals.h
    includes/includes.h
    includes/op.h
    srcs/corewar_srcs/arena_ini.c
    srcs/corewar_srcs/check_process.c
    srcs/corewar_srcs/corewar.c
    srcs/corewar_srcs/gr_gl_buffer.c
    srcs/corewar_srcs/gr_vm_camera_handling.c
    srcs/corewar_srcs/gr_vm_camera_handling_rot.c
    srcs/corewar_srcs/gr_vm_handlers.c
    srcs/corewar_srcs/gr_vm_init.c
    srcs/corewar_srcs/gr_vm_init_cube.c
    srcs/corewar_srcs/gr_vm_inputs.c
    srcs/corewar_srcs/gr_vm_load_texture.c
    srcs/corewar_srcs/gr_vm_matrix.c
    srcs/corewar_srcs/gr_vm_render_opengl.c
	srcs/corewar_srcs/gr_gen_tex.c
    srcs/corewar_srcs/gr_vm_run.c
    srcs/corewar_srcs/ins_basic.c
    srcs/corewar_srcs/ins_calc.c
    srcs/corewar_srcs/ins_fork.c
    srcs/corewar_srcs/ins_index.c
    srcs/corewar_srcs/mem.c
    srcs/corewar_srcs/op.c
    srcs/corewar_srcs/opts_tokens.c
    srcs/corewar_srcs/options.c
    srcs/corewar_srcs/parse_args.c
    srcs/corewar_srcs/process.c
    srcs/corewar_srcs/values.c
    srcs/corewar_srcs/read_args.c
    srcs/corewar_srcs/utils.c)

set(ASM_FILES
    includes/asm.h
    srcs/asm_srcs/asm.c
    srcs/asm_srcs/asm_tokens.c
    srcs/asm_srcs/compile.c
    srcs/asm_srcs/op.c
    srcs/asm_srcs/opt_tokens.c
    srcs/asm_srcs/parse_asm.c
    srcs/asm_srcs/parse_opts.c
    srcs/asm_srcs/print.c
    srcs/asm_srcs/read_opts.c
    srcs/asm_srcs/utils.c
    srcs/asm_srcs/write.c)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

LINK_DIRECTORIES(libs/libft
        libs/glhandler
		soil2
        $ENV{HOME}/.brew/lib)

add_executable(corewar ${CRWR_FILES})
add_executable(asm ${ASM_FILES})

target_link_libraries(corewar
        ft
        glhandler
        sdl2
		sdl2_ttf
        glew
        glfw
		SOIL2
        ${OPENGL_LIBRARIES}
        ${GCC_OPTIONS})

target_link_libraries(asm
        ft)
