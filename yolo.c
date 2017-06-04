#include <fcntl.h>
#include <unistd.h>
#include "libs/libft/libft.h"
int		main(void)
{
	int		fd = open("yolo.s", O_WRONLY | O_APPEND);
	char	*s = "st r3, ";
	int		i = 250;
	while (i > 0)
	{
		char *p = ft_strjoin(s, ft_itoa(i));
		write(fd, p, strlen(p));
		write(fd, "\n", 1);
		i -= 10;
	}
	close(fd);
}
