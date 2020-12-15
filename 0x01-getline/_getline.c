#include "_getline.h"

/**
 * free_all - free every node in line list
 * @lines: pointer to file lines list
 */
void free_all(line_t *lines)
{
	if (!lines)
		return;
	free(lines->buf);
	free_all(lines->next);
	free(lines);
}
/**
 * _getline - get line through access of file descriptor
 * @fd: file desc. of file we want read
 * Return: string pointing to newline of file
 */
char *_getline(const int fd)
{
	static line_t *lines;
	line_t *currln;
	char *nbytes;
	int offset;

	if (fd == -1)
	{
		free_all(lines);
		lines = NULL;
		return (NULL);
	}
	for (currln = lines; currln; currln = currln->next)
		/*if fd already, read from it*/
		if (currln->fd == fd)
		{
			return (line_parse(currln));
		}
	/*initialize vars for new line obj*/
	nbytes = malloc(sizeof(char) * READ_SIZE);
	offset = read(fd, nbytes, READ_SIZE);
	if (offset <= 0)
	{
		free(nbytes);
		return (NULL);
	}
	/*make new line obj*/
	currln = malloc(sizeof(line_t));
	if (!currln)
		return (NULL);
	currln->fd = fd;
	currln->buf = nbytes;
	currln->nbytes = offset;
	currln->next = lines;
	lines = currln;
	return (line_parse(currln));
}
/**
 * line_parse - parse buffer for line end
 * @currln: line node pointer being passed
 * Return: pointer to line parsed
 */
char *line_parse(line_t *currln)
{
	int i, j, line_b, copied_b;
	char *line, *tmp;

	line_b = 0;
	copied_b = 0;
	line = NULL;
	while (currln->nbytes > 0)
	{
		if (line_b < copied_b + currln->nbytes + 1)
		{
			line_b += currln->nbytes + 1;
			tmp = malloc(sizeof(char) * line_b);
			if (tmp == NULL)
			{
				free(line);
				return (NULL);
			}
			memcpy(tmp, line, copied_b);
			memset(tmp + copied_b, '\0', line_b - copied_b);
			free(line);
			line = tmp;
		}
		for (i = 0; i < currln->nbytes; i++)
			if (currln->buf[i] == '\n')
			{
				currln->buf[i++] = '\0';
				currln->nbytes -= i;
				memcpy(line + copied_b, currln->buf, i);
				for (j = 0; i < READ_SIZE; j++, i++)
					currln->buf[j] = currln->buf[i];
				for (; j < READ_SIZE; j++)
					currln->buf[j] = '\0';
				return (line);
			}

		memcpy(line + copied_b, currln->buf, currln->nbytes);
		copied_b += currln->nbytes;
		currln->nbytes = read(currln->fd, currln->buf, READ_SIZE);
	}
	return (line);
}
