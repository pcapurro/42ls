#include "../../include/header.h"

void	printPathError(const char* element)
{
	writeStr("ft_ls: unable to access '", 2);
	writeStr(element, 2);
	writeStr("': ", 2);

	perror("");
}

void	printOptionsError(const int value, const char* str)
{
	if (value == 0)
	{
		writeStr("ft_ls: option '", 2);
		writeStr(str, 2);
		writeStr("' was not recognized.\n", 2);
	}
	if (value == 1)
	{
		writeStr("ft_ls: invalid option -- '", 2);
		writeStr(str, 2);
		writeStr("'\n", 2);
	}
	writeStr("Type 'ft_ls --help' for more informations.\n", 2);
}

void	printElement(tInfos* infos, char* path)
{
	int		end = getStrLen(path) - 1;
	int		i = end;
	bool	value = false;
	char*	name;

	if (path[i] == '/' && i != 0)
		i--;
	while (i != 0 && path[i] != '/')
		i--;

	if (path[end] == '/')
		path[end] = '\0', value = true;

	name = path + i;
	if (i != 0)
		name = name + 1;

	if (name[0] == '/')
		name = name + 1;

	if (infos->listing == true)
	{
		if (printListing(path, name) == NULL)
			{ infos->error = 1; return ; }
	}
	else
		writeStr(name, 1);

	if (value == true)
		path[end] = '/';

	if (infos->listing == false)
		writeStr("  ", 1);
	else
		writeStr("\n", 1);
}

void	printTotal(tInfos* infos, char* originalPath, bool hidden)
{
	int			total = 0;
	char*		path = NULL;
	tStat		dirInfo;
	tDirent*	dirEntry;

	DIR* directory = opendir(originalPath);
	if (directory == NULL)
		return ;

	while (1)
	{
		dirEntry = readdir(directory);
		if (dirEntry == NULL)
			break ;

		if (dirEntry->d_name[0] == '.' && hidden == false)
			continue ;

		path = getJoin(originalPath, dirEntry->d_name, "\0");
		if (!path)
		{
			infos->error = 1;
			memoryFailed();
			closedir(directory);
			return ;
		}

		lstat(path, &dirInfo);
		total += dirInfo.st_blocks;

		free(path);
	}

	closedir(directory);

	char* number = getNumber(total / 2);

	writeStr("total ", 1);
	if (number == NULL)
		writeStr("0", 1);
	else
		writeStr(number, 1), free(number);
	writeStr("\n", 1);
}

void	printFolder(tInfos* infos, char** paths, char* originalPath)
{
	int		pathsNumber = getArrLen(paths);
	int		pathLen = getStrLen(originalPath);

	char** newArray = copyArray(paths, 1);
	if (!newArray)
		{ infos->error = 1; return ; }

	for (int i = 0, end = 0; newArray[i] != NULL; i++)
	{
		end = getStrLen(newArray[i]) - 1;
		if (newArray[i][end] == '/')
			newArray[i][end] = '\0';
	}

	if (infos->listing == true)
		printTotal(infos, originalPath, infos->hidden);

	for (int count = 0, element = 0; count != pathsNumber; count++)
	{
		if (infos->time == true)
			element = getElementInTimeOrder(newArray, pathsNumber, infos->reverse);
		else
			element = getElementInAlphOrder(newArray, pathsNumber, pathLen, infos->reverse);
		printElement(infos, paths[element]);

		if (infos->error == 1)
		{
			for (int i = 0; i != pathsNumber; i++)
			{
				if (newArray[i] != NULL)
					free(newArray[i]);
			}
			free(newArray);
			return ;
		}

		free(newArray[element]);
		newArray[element] = NULL;
	}
	free(newArray);
}

void	*printListing(char* path, char* name)
{
	char*	str = NULL;
	tStat	info;

	lstat(path, &info);

	str = getData(path);
	if (str != NULL)
		{ writeStr(str, 1), writeStr(" ", 1), free(str); }
	else
		return (NULL);

	str = getSize(path);
	if (str != NULL)
		{ writeStr(str, 1), writeStr(" ", 1), free(str); }
	else
		return (NULL);

	str = getDate(path);
	if (str != NULL)
		{ writeStr(str, 1), writeStr(" ", 1); }
	else
		return (NULL);

	writeStr(name, 1);

	if (S_ISLNK(info.st_mode) == true)
	{
		str = getLink(path);
		if (str != NULL)
		{
			writeStr(" ", 1);
			writeStr(str, 1);
			writeStr(" ", 1);
			free(str);
		}
	}

	return (path);
}
