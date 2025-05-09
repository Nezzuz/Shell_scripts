#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#define BUFFER_SIZE 2

static char*		ft_strjoin(char* s1, char* s2, bool freefirst, bool freesecond)
{
	size_t	i = 0;	
	size_t	ii = 0;	
	char*	jbuff;

	while (s1[i])
		i++;
	while (s2[ii])
		ii++;
	jbuff = (char*)malloc(sizeof(char) * (i + ii));
	i = 0;
	ii = 0;
	while (s1[i])
		jbuff[i] = s1[i], i++;

	while (s2[ii])
		jbuff[i + ii] = s2[ii], ii++;
	jbuff[i + ii] = '\0';
	if (freefirst == true)
		free(s1), s1 = (void*)0;
	if (freesecond == true)
		free(s2), s2 = (void*)0;
	return (jbuff);
}

static inline size_t	ft_strlen(const char *s)
{
	size_t	i = 0;

	while (s[i])
		i++;
	return (i);

}

static void		ft_bzero(void* s, size_t n)
{
	size_t	i = 0;

	while (i < n)
	{
		*(char*)(s + i) = 0;
		i++;
	}
}

static void*		ft_memchr(const void* s, int c, size_t n)
{
	size_t	i = 0;

	while (s != (void*)0 && i < n)
	{
		if (*(unsigned char*)(s + i) == c)
			return ((unsigned char*)(s + i));	
		i++;
	}
	return ((void*)0);
}

static char*		front_excess(const char* str, int c, int i)
{
	char*	substr;
	int	ii;
       
	substr = (void*)0;
	while (str[i] != c)
		i++;
	substr = (char*)malloc(sizeof(char) * (i + 1));
	ii = i;
	i = 0;
	while (i < ii && str[i] != '\0')
	{
		substr[i] = str[i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static void		handle_newline(char** line, char buffer[BUFFER_SIZE], size_t buff_nbytes)
{
	size_t	i = 0;
	size_t	ii = 0;
	char*	ptr2ln;

	line[0] = ft_strjoin(line[0], front_excess(buffer, '\n', i), true , true);
	ptr2ln = ft_memchr(buffer, '\n', BUFFER_SIZE) + 1;
	while (*ptr2ln)
	{
		buffer[ii] = *ptr2ln;
		ii++;
		ptr2ln = ptr2ln + 1;
	}
	ft_bzero(&buffer[ii], (buff_nbytes - ii));
}

char*			get_next_line(int fd)
{
	char*		line;
	static char	buffer[BUFFER_SIZE];

	line = (char*)malloc(sizeof(char) * 1);
	line[0] = '\0';
	if (buffer[0] == '\0')
		buffer[0] = '\0';
	if (buffer[0] != '\0' && ft_memchr(buffer, '\n', BUFFER_SIZE) == (void*)0)
		line = ft_strjoin(line, buffer, true, false);
	while (read(fd, buffer, BUFFER_SIZE) > 0 && ft_strlen(buffer) > 0)
	{
		if (ft_memchr(buffer, '\n', BUFFER_SIZE) == (void*)0)
			line = ft_strjoin(line, buffer, true, false);
		else
			return (handle_newline(&line, buffer, ft_strlen(buffer)), line);
	}
	if (line)
		return (handle_newline(&line, buffer, ft_strlen(buffer)), line);
	else if (ft_strlen(buffer) > 0)
		return (ft_bzero(buffer, ft_strlen(buffer)), (void*)0);
	return ((void*)0);
}

int			main(void)
{
	/* char*	str = "Hola buenas tardes"; */
	/* char	c = 'b'; */
	/* int	n = 10; */
	int 	fd = open("file.txt", O_RDONLY);
	char*	line1 = get_next_line(fd);
	char*	line2 = get_next_line(fd);
	char*	line3 = get_next_line(fd);
	char*	line4 = get_next_line(fd);
       	/* char*	gotit = ft_memchr(str, c, n); */
       	/* ft_bzero(gotit, 8); */
	/* bzero(gotit, 8); */
	/* printf("%s\n", gotit); */
	printf("%s\n", line1);
	printf("%s\n", line2);
	printf("%s\n", line3);
	printf("%s\n", line4);
	/* printf("%s\n", line2); */

	free(line1);
	free(line2);
	free(line3);
	free(line4);
	return (close(fd), 0);
}
