#include "corewar.h"
#include "gr_vm_internals.h"

GLuint load_bmp_to_opengl(char *b)
{
	int				fd;
	GLuint			textID;
	unsigned char	header[54];
	unsigned int	size[3];

	if ((fd = open(b, O_RDONLY)) < 0 ||
		ft_strcmp(ft_strchr(b, '.'), ".bmp"))
	exit(0);
	read(fd, header, 54);
	size[0] = *(int*)&(header[0x22]);
	size[1] = *(int*)&(header[0x12]);
	size[2] = *(int*)&(header[0x16]);
	b = malloc(size[0] * sizeof(unsigned char));
	read(fd, b, size[0]);
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &(textID));
	glBindTexture(GL_TEXTURE_2D, (textID));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
	size[1], size[2], 0, GL_BGR, GL_UNSIGNED_BYTE, b + 84);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	free(b);
	return (textID);
}

void load_bmp_to_42(char *b, uint32_t *out)
{
	int				fd;
	unsigned char	header[54];
	unsigned int	size[3];

	if ((fd = open(b, O_RDONLY)) < 0 ||
		ft_strcmp(ft_strchr(b, '.'), ".bmp"))
	exit(0);
	read(fd, header, 54);
	size[0] = *(int*)&(header[0x22]);
	size[1] = *(int*)&(header[0x12]);
	size[2] = *(int*)&(header[0x16]);
	read(fd, out, 84);
	read(fd, out, size[0] * 4);
}

void load_light(uint32_t in[MEM_SIZE], float out[MEM_SIZE * 4], float models[][9], t_gr_vm *cxt)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		out[i * 4 + 3] = models[i][1];
		if (cxt->anim42)
		{
			out[i * 4 + 2] = !(float)cxt->text42[i * 3] * (float)rand() / RAND_MAX;
			out[i * 4 + 1] = !(float)cxt->text42[i * 3 + 1] * (float)rand() / RAND_MAX;
			out[i * 4 + 0] = !(float)cxt->text42[i * 3 + 2] * (float)rand() / RAND_MAX;
		}
		i++;
	}
	if (!cxt->anim42)
	{
		int e = (rand() % MEM_SIZE) * 4;
		cxt->col[e] =  (float)rand() / RAND_MAX;
		cxt->col[e + 1] = (float)rand() / RAND_MAX;
		cxt->col[e + 2] = (float)rand() / RAND_MAX;
        i = 0;
	}
}

GLuint light_to_texture(float l[MEM_SIZE * 4])
{
	GLuint textID;

	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &(textID));
	glBindTexture(GL_TEXTURE_2D, (textID));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	sqrt(MEM_SIZE), sqrt(MEM_SIZE), 0, GL_BGRA, GL_FLOAT, l);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	return (textID);
}
