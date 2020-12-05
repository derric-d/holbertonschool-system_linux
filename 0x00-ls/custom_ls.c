#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>


void parse_curdir(char **argv);
void parse_flagdir(char **argv);
/**
 * _ls - custom ls func
 * @dir: directory entity passed
 * @ls_a: all option
 * @ls_1: single column option
 * @ls_A: almost all option
 * Return: void
 */
void _ls(const char *dir, int ls_a, int ls_1, int ls_A)
{
	struct dirent *ptrFile;
	DIR *ptrDir;

	ptrDir = opendir(dir);
	if (!ptrDir)
	{
		if (errno == ENOENT)
			perror("hls: cannot access ");
		else
			perror("Unable to read directory");
		exit(EXIT_FAILURE);
	}
	while ((ptrFile = readdir(ptrDir)) != NULL)
	{
		if (ls_A && strlen(ptrFile->d_name) > 2)
			printf("%s ", ptrFile->d_name);
		if (!ls_a && ptrFile->d_name[0] == '.')
			continue;
		if (!ls_A)
			printf("%s ", ptrFile->d_name);
		if (ls_1)
			printf("\n");
	}
	if (!ls_1)
		printf("\n");
	/*close dir*/
	closedir(ptrDir);

}

/**
 * main - entry
 * @argc: count of args
 * @argv: vector of args
 * Return: 0 on success
 */
int main(int argc, char **argv)
{

	if (argc == 1)
		_ls(".", 0, 0, 0);
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			parse_curdir(argv);
		} else
		_ls(argv[1], 0, 0, 0);
	}
	else if (argc == 3)
	{
		if (argv[1][0] != '-')
		{
			perror("Incorrect option error");
			exit(EXIT_FAILURE);
		}
		parse_flagdir(argv);
	}

	return (0);
}



/**
 * parse_curdir - parse dir with 2 args
 * @argv: arg vector
 */
void parse_curdir(char **argv)
{
	int ls_a = 0, ls_1 = 0, ls_A = 0;
	char *p = (char *)(argv[1] + 1);

	while (*p)
	{
		if (*p == '1')
			ls_1 = 1;
		else if (*p == 'a')
		{
			ls_a = 1;
		} else if (*p == 'A')
			ls_A = 1;
		else
		{
			perror("Unknown option error");
			exit(EXIT_FAILURE);
		}
		p++;
	}
	_ls(".", ls_a, ls_1, ls_A);
}

/**
 * parse_flagdir - arg with options
 * @argv: argvector
 */
void parse_flagdir(char **argv)
{
	int ls_a = 0, ls_1 = 0, ls_A = 0;
	char *p = (char *)(argv[1] + 1);

	while (*p)
	{
		if (*p == '1')
			ls_1 = 1;
		else if (*p == 'a')
			ls_a = 1;
		else if (*p == 'A')
			ls_A = 1;
		else
		{
			perror("Unknown option error");
			exit(EXIT_FAILURE);
		}
		p++;
	}
	_ls(argv[2], ls_a, ls_1, ls_A);
}
