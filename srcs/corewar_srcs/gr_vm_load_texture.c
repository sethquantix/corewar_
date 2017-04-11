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

void load_light(uint32_t in[MEM_SIZE], uint32_t out[MEM_SIZE])
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		out[i] = 0x00FF00FF;
		i++;
	}
}

GLuint light_to_texture(uint32_t l[MEM_SIZE])
{
	GLuint textID;

	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &(textID));
	glBindTexture(GL_TEXTURE_2D, (textID));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	sqrt(MEM_SIZE), sqrt(MEM_SIZE), 0, GL_RGBA, GL_UNSIGNED_BYTE, l);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	return (textID);
}
