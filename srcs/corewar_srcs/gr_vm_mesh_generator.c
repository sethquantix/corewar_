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

static void init_instancing()
{
	GLuint instanceVBO;

	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	glVertexAttribDivisor(2, 1);  
}

GLuint			generate_cube(uint n)
{
	GLuint		vaoid;

	createVBO_VNT(g_cube, sizeof(g_cube) / sizeof(float) / 8, vaoid);
	return (vaoid);
}
