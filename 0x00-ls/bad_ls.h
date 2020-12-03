#ifndef LS_H
#define LS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

/**
 * struct option_S - struct to hold options
 * @ls_a: the 'all' option (hidden dirs)
 * @ls_1: print single column
 * @ls_A: show almost all (hidden dirs not curr or prev)
 */
typedef struct option_s
{
	int ls_a;
	int ls_1;
	int ls_A;
} ops_t;

/**
 * struct arg_s - struct to hold info about ls arguments
 * @ac: arg count
 * @av: argument content (vector)
 * @op: options provided
 */
typedef struct arg_s
{
	int ac;
	char **av;
	ops_t op;
	char *dir;
} arg_t;


/*functions*/
void get_ops(arg_t *args);



#endif
