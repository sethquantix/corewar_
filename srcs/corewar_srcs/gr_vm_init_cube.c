#include "corewar.h"
#include "gr_vm_internals.h"

static const float g_cube[] = {
	-0.5, 0, 0.5, 0, -1, 0, 0, 1, // LBB
	0.5, 0, 0.5, 0, -1, 0, 1, 1, // RBB
	0.5, 0, -0.5, 0, -1, 0, 1, 0, // RBF
	0.5, 0, -0.5, 0, -1, 0, 1, 0, // RBF
	-0.5, 0, -0.5, 0, -1, 0, 0, 0, // LBF
	-0.5, 0, 0.5, 0, -1, 0, 0, 1, // LBB

	-0.5, 1, 0.5, 0, 1, 0, 0, 1, // LUB
	0.5, 1, 0.5, 0, 1, 0, 1, 1, // RUB
	0.5, 1, -0.5, 0, 1, 0, 1, 0, // RUF
	0.5, 1, -0.5, 0, 1, 0, 1, 0, // RUF
	-0.5, 1, -0.5, 0, 1, 0, 0, 0, // LUF
	-0.5, 1, 0.5, 0, 1, 0, 0, 1, // LUB

	-0.5, 0, 0.5, -1, 0, 0, 0, 1, // LBB
	-0.5, 0, -0.5, -1, 0, 0, 1, 1, // LBF
	-0.5, 1, -0.5, -1, 0, 0, 1, 0, // LUF
	-0.5, 1, -0.5, -1, 0, 0, 1, 0, // LUF
	-0.5, 1, 0.5, -1, 0, 0, 0, 0, // LUB
	-0.5, 0, 0.5, -1, 0, 0, 0, 1, // LBB

	0.5, 0, 0.5, 1, 0, 0, 0, 1, // RBB
	0.5, 0, -0.5, 1, 0, 0, 1, 1, // RBF
	0.5, 1, -0.5, 1, 0, 0, 1, 0, // RUF
	0.5, 1, -0.5, 1, 0, 0, 1, 0, // RUF
	0.5, 1, 0.5, 1, 0, 0, 0, 0, // RUB
	0.5, 0, 0.5, 1, 0, 0, 0, 1, // RBB

	0.5, 0, -0.5, 0, 0, -1, 0, 1, // RBF
	-0.5, 0, -0.5, 0, 0, -1, 1, 1, // LBF
	-0.5, 1, -0.5, 0, 0, -1, 1, 0, // LUF
	-0.5, 1, -0.5, 0, 0, -1, 1, 0, // LUF
	0.5, 1, -0.5, 0, 0, -1, 0, 0, // RUF
	0.5, 0, -0.5, 0, 0, -1, 0, 1, // RBF

	0.5, 0, 0.5, 0, 0, 1, 0, 1, // RBB
	-0.5, 0, 0.5, 0, 0, 1, 1, 1, // LBB
	-0.5, 1, 0.5, 0, 0, 1, 1, 0, // LUB
	-0.5, 1, 0.5, 0, 0, 1, 1, 0, // LUB
	0.5, 1, 0.5, 0, 0, 1, 0, 0, // RUB
	0.5, 0, 0.5, 0, 0, 1, 0, 1 // RBB
};

static float g_board[] = {
	-71.3, 12, -128, 0, 1,
	-71.3, 0, -128, 0, 0,
	71.3, 0, -128, 1, 0,
	71.3, 0, -128, 1, 0,
	71.3, 12, -128, 1, 1,
	-71.3, 12, -128, 0, 1
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

static uint32_t		createVBO_VNT(float *vertices, int *faces,
	uint32_t vertex_size, GLuint vaoId)
{
	GLuint  vertexBufferID;
	GLuint  facesBufferID;

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

	glGenBuffers(1, &facesBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, facesBufferID);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(int), faces, GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 1, GL_INT, sizeof(GLint), (void *)0);
	return (vertexBufferID);
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

static GLuint 		init_values()
{
	GLuint	valVBO;

	glGenBuffers(1, &valVBO);
	glBindBuffer(GL_ARRAY_BUFFER, valVBO);
	glEnableVertexAttribArray(8);
	glVertexAttribIPointer(8, 1, GL_UNSIGNED_INT, sizeof(GLuint), (void *)(0));
	glVertexAttribDivisor(8, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return (valVBO);
}

static void			init_pos(t_gr_vm *cxt)
{
	uint i;

	i = 0;
	while (i < MEM_SIZE)
	{
		cxt->model[i][0] = (float)((i % (int)sqrt(MEM_SIZE) -
			(sqrt(MEM_SIZE)) / 2) * 2.3);
		cxt->model[i][1] = 0;
		cxt->model[i][2] = (float)((i / (int)sqrt(MEM_SIZE) -
			(sqrt(MEM_SIZE)) / 2) * 2.3);
		cxt->model[i][6] = 1;
		cxt->model[i][7] = 1;
		cxt->model[i][8] = 1;
        cxt->scale[i] = 1;
		i++;
	}
}

static void			gen_board(t_gr_vm *cxt)
{
	GLuint 	vbo;
	int		i;
	float 	h;

	h = (g_board[10] - g_board[0]) / (float)WIN_WIDTH * (float)WIN_HEIGHT;
	i = 0;
	while (i < 6)
	{
		if (g_board[5 * i + 1] == 0)
			g_board[5 * i + 1] = 12 + h;
		i++;
	}
	glGenVertexArrays(1, &cxt->vao_board);
	glBindVertexArray(cxt->vao_board);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float) * 5, &g_board[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float)*3));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLuint				generate_cube(t_gr_vm *cxt)
{
	GLuint		vao;

	glGenVertexArrays(1, &vao);
	createVBO_VNT((float *)g_cube, (int *)g_faces,
		sizeof(g_cube) / sizeof(float) / 8, vao);
	cxt->vao = vao;
	cxt->matVBO = init_instancing();
	cxt->valVBO = init_transfer();
	cxt->arenaVBO = init_values();
	init_pos(cxt);
	glGenVertexArrays(1, &cxt->vao_box);
	createVBO_VNT((float *)g_cube, (int *)g_faces,
		sizeof(g_cube) / sizeof(float) / 8, cxt->vao_box);
	ft_printf("box : %d\n", cxt->vao_box);
	gen_board(cxt);
	return (vao);
}
