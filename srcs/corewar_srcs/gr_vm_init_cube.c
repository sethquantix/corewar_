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

	0.5, -0.5, -0.5, 0, 0, -1, 0, 1,
	-0.5, -0.5, -0.5, 0, 0, -1, 1, 1,
	-0.5, 0.5, -0.5, 0, 0, -1, 1, 0,
	-0.5, 0.5, -0.5, 0, 0, -1, 1, 0,
	0.5, 0.5, -0.5, 0, 0, -1, 0, 0,
	0.5, -0.5, -0.5, 0, 0, -1, 0, 1,

	0.5, -0.5, 0.5, 0, 0, 1, 0, 1,
	-0.5, -0.5, 0.5, 0, 0, 1, 1, 1,
	-0.5, 0.5, 0.5, 0, 0, 1, 1, 0,
	-0.5, 0.5, 0.5, 0, 0, 1, 1, 0,
	0.5, 0.5, 0.5, 0, 0, 1, 0, 0,
	0.5, -0.5, 0.5, 0, 0, 1, 0, 1,
};

static uint32_t		createVBO_VNT(float *vertices, uint32_t vertex_size, uint32_t vaoId)
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
	return (vertexBufferID);
}

static GLuint		init_instancing()
{
	GLuint instanceVBO;

	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribDivisor(3, 1);

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(sizeof(GLfloat)*3));
	glVertexAttribDivisor(4, 1);
	return (instanceVBO);
}

static void			init_pos(t_gr_vm *cxt)
{
	uint i;

	i = 0;
	while (i < MEM_SIZE)
	{
		cxt->model[i][0] = (i % (int)sqrt(MEM_SIZE) - (sqrt(MEM_SIZE)) / 2) * 2.3;
		cxt->model[i][1] = 0;
		cxt->model[i][2] = (i / (int)sqrt(MEM_SIZE) - (sqrt(MEM_SIZE)) / 2) * 2.3;
		i++;
	}
}

GLuint				generate_cube(t_gr_vm *cxt)
{
	GLuint		vaoid;

	glGenVertexArrays(1, &vaoid);
	createVBO_VNT(g_cube, sizeof(g_cube) / sizeof(float) / 8, vaoid);
	cxt->vao = vaoid;
	cxt->matVBO = init_instancing();
	init_pos(cxt);
	return (vaoid);
}
