#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>

# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

# include <sys/stat.h>
# include <sys/xattr.h>

struct sInfos
{
	bool	listing;
	bool	recursive;
	bool	hidden;
	bool	reverse;
	bool	time;

	bool	list;

	bool	options;
	char**	paths;

	bool	error;
};

typedef struct sInfos	tInfos;

typedef struct dirent	tDirent;
typedef struct stat		tStat;

int		getStrLen(const char* str);
int		getArrLen(char** str);
char*	getDup(const char* str);
char*	getJoin(const char* s1, const char* s2, const char* s3);
void	writeStr(const char* str, int fd);

void	memoryFailed(void);
void	systemFailed(void);

void*	addElement(char*** array, const char* element);
void*	findElement(char** array, char* element);

void	freeArray(char** array);

bool	isValidOption(const char *str);
void	printOptionsError(const int value, const char* str);
void	getOption(char* argv, tInfos* infos);
void	getOptions(char** argv, tInfos* infos);

void	printListError(const char* element);
char*	getName(char* path);

void	searchForPaths(char** argv, tInfos* infos);
void	getPaths(char** argv, tInfos* infos);

bool	isFolder(const char* name, const unsigned type, tInfos* infos);
bool	isSame(char* str1, const char* str2);

int		getElementInTimeOrder(char** array, int pathsNumber, int pathsLen);
int		getElementInAlphOrder(char** array, int pathsNumber, int pathsLen);

void	list(tInfos* infos, char** paths, int value);
void	preList(tInfos* infos);

void	setToDefault(tInfos* infos);
void	printHelp(void);
bool	isHelp(const char* str);

int		main(const int argc, char** argv);

#endif