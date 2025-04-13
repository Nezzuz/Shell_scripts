#include <unistd.h>
#include <fcntl.h>

void str(int fd, char *str)
{
	while (*str)
		write(fd, str++, 1);
}

int main(int ac, char **av)
{
	int	fd;
	int	oldout;
	char	buffer[1];

	if (ac != 2)
		return (str(2, "There must be the name of a file as second argument\n"), 1);
	fd = open(av[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((oldout = dup(1)) == -1)
		return (close(fd), str(2, "There aren't available file descriptors\n"), 2);
	if (dup2(fd, 1) == -1)
		return (close(fd), close(oldout), str(2, "An error happened while duplicating a file descriptor\n"), 3);
	while (read(STDIN_FILENO, buffer, 1) > 0)
		str(fd, buffer), str(oldout, buffer);
	return (close(fd), close(oldout), 0);
}

