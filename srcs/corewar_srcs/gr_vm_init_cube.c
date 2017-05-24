#include "corewar.h"
#include "gr_vm_internals.h"
#include "../../libs/glhandler/includes/gl_handler.h"

static const float g_cube[] = {

	-0.5, 0, 0.5, 0, -1, 0, 0, 1,
	0.5, 0, 0.5, 0, -1, 0, 1, 1,
	0.5, 0, -0.5, 0, -1, 0, 1, 0,
	0.5, 0, -0.5, 0, -1, 0, 1, 0,
	-0.5, 0, -0.5, 0, -1, 0, 0, 0,
	-0.5, 0, 0.5, 0, -1, 0, 0, 1,

	-0.5, 1, 0.5, 0, 1, 0, 0, 1,
	0.5, 1, 0.5, 0, 1, 0, 1, 1,
	0.5, 1, -0.5, 0, 1, 0, 1, 0,
	0.5, 1, -0.5, 0, 1, 0, 1, 0,
	-0.5, 1, -0.5, 0, 1, 0, 0, 0,
	-0.5, 1, 0.5, 0, 1, 0, 0, 1,

	-0.5, 0, 0.5, -1, 0, 0, 0, 1,
	-0.5, 0, -0.5, -1, 0, 0, 1, 1,
	-0.5, 1, -0.5, -1, 0, 0, 1, 0,
	-0.5, 1, -0.5, -1, 0, 0, 1, 0,
	-0.5, 1, 0.5, -1, 0, 0, 0, 0,
	-0.5, 0, 0.5, -1, 0, 0, 0, 1,

	0.5, 0, 0.5, 1, 0, 0, 0, 1,
	0.5, 0, -0.5, 1, 0, 0, 1, 1,
	0.5, 1, -0.5, 1, 0, 0, 1, 0,
	0.5, 1, -0.5, 1, 0, 0, 1, 0,
	0.5, 1, 0.5, 1, 0, 0, 0, 0,
	0.5, 0, 0.5, 1, 0, 0, 0, 1,

	0.5, 0, -0.5, 0, 0, -1, 0, 1,
	-0.5, 0, -0.5, 0, 0, -1, 1, 1,
	-0.5, 1, -0.5, 0, 0, -1, 1, 0,
	-0.5, 1, -0.5, 0, 0, -1, 1, 0,
	0.5, 1, -0.5, 0, 0, -1, 0, 0,
	0.5, 0, -0.5, 0, 0, -1, 0, 1,

	0.5, 0, 0.5, 0, 0, 1, 0, 1,
	-0.5, 0, 0.5, 0, 0, 1, 1, 1,
	-0.5, 1, 0.5, 0, 0, 1, 1, 0,
	-0.5, 1, 0.5, 0, 0, 1, 1, 0,
	0.5, 1, 0.5, 0, 0, 1, 0, 0,
	0.5, 0, 0.5, 0, 0, 1, 0, 1
};

static const int g_faces[] = {
		F_DOWN,
		F_DOWN,
		F_DOWN,
		F_DOWN,
		F_DOWN,
		F_DOWN,
		F_UP,
		F_UP,
		F_UP,
		F_UP,
		F_UP,
		F_UP,
		F_LEFT,
		F_LEFT,
		F_LEFT,
		F_LEFT,
		F_LEFT,
		F_LEFT,
		F_RIGHT,
		F_RIGHT,
		F_RIGHT,
		F_RIGHT,
		F_RIGHT,
		F_RIGHT,
		F_BACK,
		F_BACK,
		F_BACK,
		F_BACK,
		F_BACK,
		F_BACK,
		F_FRONT,
		F_FRONT,
		F_FRONT,
		F_FRONT,
		F_FRONT,
		F_FRONT
};

static uint32_t		createVBO_VNT(float *vertices, uint32_t vertex_size, uint32_t vaoId)
{
	GLuint  vertexBufferID;

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

static GLuint 		init_faces(const int *faces)
{
	GLuint  facesBufferID;

	glGenBuffers(1, &facesBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, facesBufferID);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(int), faces, GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 1, GL_INT, sizeof(GLint), (void *)0);
	return (facesBufferID);
}

static GLuint		init_instancing()
{
	GLuint instanceVBO;

	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glEnableVertexAttribArray(4);

	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribDivisor(4, 1);

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(sizeof(GLfloat)*3));
	glVertexAttribDivisor(5, 1);

	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(sizeof(GLfloat)*6));
	glVertexAttribDivisor(6, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return (instanceVBO);
}

static GLuint 		init_transfer()
{
	GLuint	transferVBO;

	glGenBuffers(1, &transferVBO);
	glBindBuffer(GL_ARRAY_BUFFER, transferVBO);
	glEnableVertexAttribArray(7);
	glVertexAttribIPointer(7, 1, GL_UNSIGNED_INT, sizeof(GLuint), (void *)(0));
	glVertexAttribDivisor(7, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return (transferVBO);
}

static void			init_pos(t_gr_vm *cxt)
{
	uint i;

	i = 0;
	while (i < MEM_SIZE)
	{
		cxt->model[i][0] = (float)((i % (int)sqrt(MEM_SIZE) - (sqrt(MEM_SIZE)) / 2) * 2.3);
		cxt->model[i][1] = 0;
		cxt->model[i][2] = (float)((i / (int)sqrt(MEM_SIZE) - (sqrt(MEM_SIZE)) / 2) * 2.3);
		cxt->model[i][6] = 1;
		cxt->model[i][7] = 1;
		cxt->model[i][8] = 1;
        cxt->scale[i] = 1;
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
	cxt->valVBO = init_transfer();
	cxt->faceVBO = init_faces(g_faces);
	init_pos(cxt);
	return (vaoid);
}
