
#include "ft_printf.h"
#include <fcntl.h>

int		main(int ac, char **av)
{
	char	*line;
	int		fd;

	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		ft_putendl(line);
	return (0);
}

