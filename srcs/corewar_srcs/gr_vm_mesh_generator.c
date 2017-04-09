#include "corewar.h"
#include "gr_vm_internals.h"
#include "../../libs/glhandler/includes/gl_handler.h"

static const float g_cube[] = {

	-0.5, -0.5, 0.5, 0, -1, 0, 0, 1,
	0.5, -0.5, 0.5, 0, -1, 0, 1, 1,
	0.5, -0.5, -0.5, 0, -1, 0, 1, 0,
	0.5, -0.5, -0.5, 0, -1, 0, 1, 0,
	-0.5, -0.5, -0.5, 0, -1, 0, 0, 0,
	-0.5, -0.5, 0.5, 0, -1, 0, 0, 1,

	-0.5, 0.5, 0.5, 0, 1, 0, 0, 1,
	0.5, 0.5, 0.5, 0, 1, 0, 1, 1,
	0.5, 0.5, -0.5, 0, 1, 0, 1, 0,
	0.5, 0.5, -0.5, 0, 1, 0, 1, 0,
	-0.5, 0.5, -0.5, 0, 1, 0, 0, 0,
	-0.5, 0.5, 0.5, 0, 1, 0, 0, 1,

	-0.5, -0.5, 0.5, -1, 0, 0, 0, 1,
	-0.5, -0.5, -0.5, -1, 0, 0, 1, 1,
	-0.5, 0.5, -0.5, -1, 0, 0, 1, 0,
	-0.5, 0.5, -0.5, -1, 0, 0, 1, 0,
	-0.5, 0.5, 0.5, -1, 0, 0, 0, 0,
	-0.5, -0.5, 0.5, -1, 0, 0, 0, 1,

	0.5, -0.5, 0.5, 1, 0, 0, 0, 1,
	0.5, -0.5, -0.5, 1, 0, 0, 1, 1,
	0.5, 0.5, -0.5, 1, 0, 0, 1, 0,
	0.5, 0.5, -0.5, 1, 0, 0, 1, 0,
	0.5, 0.5, 0.5, 1, 0, 0, 0, 0,
	0.5, -0.5, 0.5, 1, 0, 0, 0, 1,

	0.5, -0.5, 0.5, 0, 0, 1, 0, 1,
	-0.5, -0.5, 0.5, 0, 0, 1, 1, 1,
	-0.5, 0.5, 0.5, 0, 0, 1, 1, 0,
	-0.5, 0.5, 0.5, 0, 0, 1, 1, 0,
	0.5, 0.5, 0.5, 0, 0, 1, 0, 0,
	0.5, -0.5, 0.5, 0, 0, 1, 0, 1,

	0.5, -0.5, 0.5, 0, 0, -1, 0, 1,
	-0.5, -0.5, 0.5, 0, 0, -1, 1, 1,
	-0.5, 0.5, 0.5, 0, 0, -1, 1, 0,
	-0.5, 0.5, 0.5, 0, 0, -1, 1, 0,
	0.5, 0.5, 0.5, 0, 0, -1, 0, 0,
	0.5, -0.5, 0.5, 0, 0, -1, 0, 1,
};

static void		push_plane(GLfloat *data)
{
	;
}

static GLfloat	*push_cube(GLfloat *data, float offx, float offy, float sz)
{
	;
}

static GLfloat	*create_vertex(uint n)
{
	int		i;
	int		j;
	GLfloat	*ret;
	GLfloat	*data;

	ret = malloc(sizeof(GLfloat) * n
		* n * 8 * 8 * 3);
	if (ret == NULL)
		exit(-1);
	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			data = push_cube(data, i, j, 1.0f / n);
			j++;
		}
		i++;
	}
	push_plane(data);
	return (ret);
}

/*
 ** This function create a mesh with a "numCube" cube
 ** and return a vao ID to this mesh.
*/

GLuint			generate_cube(uint n)
{
	GLfloat		*vertex;
	GLuint		vaoid;

	vertex = create_vertex(n);
	return (vaoid);
}
