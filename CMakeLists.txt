cmake_minimum_required(VERSION 3.5)
project(_corewar)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_C_FLAGS "-g -fsanitize=address")

include_directories(
	includes
	includes/asm
	includes/corewar
	includes/corewar/graphics
	includes/corewar/internals
	lib/soil2/incs
	lib/libft
	lib/glhandler/includes
	$ENV{HOME}/.brew/include
	)

set(CRWR_INC
	includes/corewar/corewar.h
	includes/corewar/graphics/gr_structs.h
	includes/corewar/graphics/gr_types.h
    includes/corewar/graphics/gr_vm.h
	includes/corewar/graphics/gr_vm_internals.h
	includes/corewar/internals/crwr_defines.h
	includes/corewar/internals/crwr_globals.h
	includes/corewar/internals/crwr_structs.h
	includes/corewar/internals/crwr_types.h
	includes/corewar/includes.h
    includes/op.h
)

set(ASM_INC
	includes/asm/asm.h
	includes/asm/decompile.h
)

file(GLOB_RECURSE CRWR_SRCS srcs/corewar_srcs/*.c)
file(GLOB_RECURSE ASM_SRCS srcs/asm_srcs/*.c)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

LINK_DIRECTORIES(
		lib/libft
        lib/glhandler
		lib/soil2
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
