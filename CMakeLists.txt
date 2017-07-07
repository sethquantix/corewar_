cmake_minimum_required(VERSION 3.5)
project(_corewar)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_C_FLAGS "-g -fsanitize=address")

include_directories(includes
		soil2/incs
        libs/libft
		libs/glhandler/includes
		$ENV{HOME}/.brew/include)

set(CRWR_INC
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
<<<<<<< HEAD
)
set(ASM_INC
=======
    srcs/corewar_srcs/arena_ini.c
    srcs/corewar_srcs/check_process.c
    srcs/corewar_srcs/corewar.c
    srcs/corewar_srcs/gr_gl_buffer.c
    srcs/corewar_srcs/gr_vm_camera_handling.c
    srcs/corewar_srcs/gr_vm_camera_handling_rot.c
    srcs/corewar_srcs/gr_vm_handlers.c
    srcs/corewar_srcs/gr_vm_init.c
	srcs/corewar_srcs/gr_vm_ui.c
	srcs/corewar_srcs/gr_vm_ui_utils.c
    srcs/corewar_srcs/gr_vm_init_cube.c
    srcs/corewar_srcs/gr_vm_inputs.c
	srcs/corewar_srcs/gr_vm_selector.c
    srcs/corewar_srcs/gr_vm_load_texture.c
    srcs/corewar_srcs/gr_vm_matrix.c
    srcs/corewar_srcs/gr_vm_render_opengl.c
	srcs/corewar_srcs/gr_vm_styles.c
	srcs/corewar_srcs/gr_gen_tex.c
	srcs/corewar_srcs/gr_vm_keys.c
	srcs/corewar_srcs/gr_vm_gl.c
	srcs/corewar_srcs/gr_vm_run.c
	srcs/corewar_srcs/ins_basic.c
	srcs/corewar_srcs/ins_calc.c
	srcs/corewar_srcs/ins_fork.c
	srcs/corewar_srcs/ins_index.c
	srcs/corewar_srcs/mem.c
	srcs/corewar_srcs/op.c
	srcs/corewar_srcs/opts_tokens.c
	srcs/corewar_srcs/options.c
	srcs/corewar_srcs/options2.c
	srcs/corewar_srcs/parse_args.c
	srcs/corewar_srcs/process.c
	srcs/corewar_srcs/values.c
	srcs/corewar_srcs/read_args.c
    srcs/corewar_srcs/utils.c)

set(ASM_FILES
>>>>>>> ce058ee8519fe4774c6a193dbe46ddf088d6bc37
    includes/asm.h
)

file(GLOB_RECURSE CRWR_SRCS srcs/corewar_srcs/*.c)
file(GLOB_RECURSE ASM_SRCS srcs/asm_srcs/*.c)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

LINK_DIRECTORIES(libs/libft
        libs/glhandler
		soil2
        $ENV{HOME}/.brew/lib)

add_executable(corewar ${CRWR_INC} ${CRWR_SRCS})
add_executable(asm ${ASM_INC} ${ASM_SRCS})

target_link_libraries(corewar
        ft
        glhandler
        sdl2
		sdl2_ttf
        glew
		SOIL2
        ${OPENGL_LIBRARIES})

target_link_libraries(asm
		ft)
