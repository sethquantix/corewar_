#include <stdio.h>
#include <fcntl.h>

int		main(void)
{
	int fd = open("champ.s", O_WRONLY | O_APPEND);
	
	for (int i = 0; i < 10000; i++)
		dprintf(fd, "label_%d:\n", i);
	close(fd);
}
