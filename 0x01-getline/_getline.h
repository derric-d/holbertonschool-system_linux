#ifndef GETLINE_H
#define GETLINE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define READ_SIZE  1024

/**
 * struct line_s -    associates a file descriptor to its file's contents.
 * @fd: file descriptor
 * @buf: file's text
 * @nbytes: number of nbyte copied
 * @next: pointer to next line struct
 **/
typedef struct line_s
{
	int fd;
	char *buf;
	int nbytes;
	struct line_s *next;
} line_t;

char *_getline(const int fd);
char *line_parse(line_t *ln);

#endif /* GETLINE_H */
