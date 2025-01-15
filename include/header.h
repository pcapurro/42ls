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

	bool	title;

	bool	options;
	char**	paths;

	int		error;
};

typedef struct sInfos	tInfos;

typedef struct dirent	tDirent;
typedef struct stat		tStat;

bool	isFolder(const char* name, const unsigned type, tInfos* infos);
bool	isSame(char* str1, const char* str2);

void	memoryFailed(void);
void	systemFailed(void);

int		getArrLen(char** str);
void	writeStr(const char* str, int fd);
char*	getNumber(const int number);
char*	getDup(const char* str);
char*	getJoin(const char* s1, const char* s2, const char* s3);
int		getStrLen(const char* str);

void*	addElement(char*** array, const char* element);
char**	copyArray(char** array, const int value);
void*	findElement(char** array, char* element);
void	freeArray(char** array);

char*	getName(char* path);

char*	getDate(char* path);
char*	getSize(char* path);
char*	getRight(int value, mode_t info);
char*	getRights(char** data, tStat info);
char*	getOthers(char** data, tStat info);
char*	getData(char* path);
char*	getLink(char* path);

char**	getFolderElements(tInfos* infos, DIR* directory, char* originalPath);
void	reOrderFolder(tInfos* infos, char*** paths, char* originalPath);

int		getElementInTimeOrder(char** array, int pathsNumber, bool reverse);
int		getElementInAlphOrder(char** array, int pathsNumber, int pathsLen, bool reverse);

void	printPathError(const char* element);
void	printOptionsError(const int value, const char* str);

void	printElement(tInfos* infos, char* path);
void	printTotal(tInfos* infos, char* originalPath, bool hidden);
void	printFolder(tInfos* infos, char** paths, char* originalPath);
void*	printListing(char* path, char* name);

void	preList(tInfos* infos);
void	list(tInfos* infos, char** paths, int value);

void	searchForPaths(char** argv, tInfos* infos);
void	getPaths(char** argv, tInfos* infos);

bool	isValidOption(const char* str);
void	getOption(char* argv, tInfos* infos);
void	getOptions(char** argv, tInfos* infos);

void	setToDefault(tInfos* infos);
void	setToNull(tInfos* infos);
void	printHelp(void);
bool	isHelp(const char* str);

int		main(const int argc, char** argv);

#endif