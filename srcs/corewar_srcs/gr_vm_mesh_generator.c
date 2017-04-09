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
	int i;

	i = 0;
	while (i < sizeof(g_cube) / (sizeof(float) * 6))
	{
		data = g_cube[i % (sizeof(g_cube) / sizeof(GLfloat))];
		i++;
		data++;
	}
}

static GLfloat	*push_cube(GLfloat *data, float offx, float offy, float sz)
{
	int i;

	i = 0;
	while (i < sizeof(g_cube) / sizeof(float))
	{
		if ((i % 8) <= 2)
			data = (g_cube[i % (sizeof(g_cube) /
				sizeof(GLfloat))]) + offx + offy * sz;
		else
			data = g_cube[i % (sizeof(g_cube) / sizeof(GLfloat))];
		i++;
		data++;
	}
	return (data);
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
			data = push_cube(data, (i * 1.3) - (1.3 * n / 2),
				(j * 1.3) - (1.3 * n / 2), 1.0f / (n * n));
			j++;
		}
		i++;
	}
	push_plane(data);
	return (ret);
}

/*
 ** This function create a mesh with a "n * n" cubes
 ** and return a vao ID to this mesh.
*/

GLuint			generate_cube(uint n)
{
	GLfloat		*vertex;
	GLuint		vaoid;

	vertex = create_vertex(n);
	glGenVertexArrays(1, &(vaoid));
	return (vaoid);
}

uint32_t renderDataSys::createVBO_VNT(float *vertices, uint32_t vertex_size, uint32_t vaoId)
{
    GLuint  vertexBufferID;
    GLuint  normalBufferID;
    GLuint  textCoordBufferID;

    glBindVertexArray(vaoId);

    glGenBuffers(1, &(vertexBufferID));
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER,  vertex_size * sizeof(float) * 8, &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float)*3));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float)*6));
    return vertexBufferID;
}
