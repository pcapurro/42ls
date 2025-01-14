#include "../include/header.h"

void	printListError(const char* element)
{
	writeStr("ft_ls: unable to access '", 2);
	writeStr(element, 2);
	writeStr("': ", 2);

	perror("");
}

void	printElement(tInfos* infos, char* path)
{
	int		end = getStrLen(path) - 1;
	int		i = end;
	bool	value = false;

	if (path[i] == '/' && i != 0)
		i--;
	while (i != 0 && path[i] != '/')
		i--;

	if (path[end] == '/')
		path[end] = '\0', value = true;

	char* name = path + i;
	if (i != 0)
		name = name + 1;

	if (infos->listing == true)
		printListing(path, name);
	else
		writeStr(name, 1);

	if (value == true)
		path[end] = '/';

	if (infos->listing == false)
		writeStr("  ", 1);
	else
		writeStr("\n", 1);
}

char**	getFolderElements(tInfos* infos, DIR* directory, char* originalPath)
{
	tDirent*	dirEntry = NULL;
	char**		newElements = NULL;
	char*		element = NULL;

	while (1)
	{
		dirEntry = readdir(directory);
		if (dirEntry == NULL)
			break ;

		if (infos->hidden == false \
			&& dirEntry->d_name[0] == '.')
			continue ;

		if (dirEntry->d_type == DT_DIR)
			element = getJoin(originalPath, dirEntry->d_name, "/");
		else
			element = getJoin(originalPath, dirEntry->d_name, "\0");

		addElement(&newElements, element);
		free(element);
		element = NULL;
	}

	return (newElements);
}

char*	getName(char* path)
{
	int		i = 0;
	char*	name;

	while (path[i] != '\0')
		i++;
	i--;
	if (path[i] == '/')
		i--;

	while (i != 0 && path[i] != '/')
		i--;

	name = path + i;
	if (name[0] == '/' && name[1] != '\0')
		name += 1;

	if (isSame("./", name) == true || isSame("../", name) == true)
		return (NULL);

	return (name);
}

void	printTotal(char* originalPath, bool hidden)
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
			{ closedir(directory); return ; }

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

void	printFolder(tInfos* infos, DIR* directory, char** paths, char* originalPath)
{
	int		pathsNumber = getArrLen(paths);
	int		pathLen = getStrLen(originalPath);
	char**	newArray;

	newArray = malloc(sizeof(char*) * (pathsNumber + 1));
	if (!newArray)
		return ;
	for (int i = 0; paths[i] != NULL; i++)
		newArray[i] = paths[i];
	newArray[pathsNumber] = NULL;

	if (infos->listing == true)
		printTotal(originalPath, infos->hidden);

	for (int count = 0, element = 0; count != pathsNumber; count++)
	{
		if (infos->time == true)
			element = getElementInTimeOrder(newArray, pathsNumber, infos->reverse);
		else
			element = getElementInAlphOrder(newArray, pathsNumber, pathLen, infos->reverse);
		printElement(infos, newArray[element]);

		newArray[element] = NULL;
	}
	free(newArray);
}

void	reOrderFolder(tInfos* infos, char*** paths, char* originalPath)
{
	int		pathsNumber = getArrLen(*paths);
	int		pathLen = getStrLen(originalPath);
	char**	newPaths = NULL;

	newPaths = malloc(sizeof(char*) * (pathsNumber + 1));
	for (int i = 0; (*paths)[i] != NULL; i++)
		newPaths[i] = (*paths)[i];
	newPaths[pathsNumber] = NULL;

	for (int i = 0, element = 0; i != pathsNumber; i++)
	{
		element = getElementInAlphOrder(*paths, pathsNumber, pathLen, infos->reverse);
		newPaths[i] = (*paths)[element];
		(*paths)[element] = NULL;
	}

	free(*paths);
	*paths = newPaths;
}

void	preList(tInfos* infos)
{
	int			count = 0;
	int			save = -1;
	DIR*		directory;

	for (int i = 0; infos->paths[i] != NULL; i++)
	{
		directory = opendir(infos->paths[i]);
		if (directory == NULL)
		{
			printElement(infos, infos->paths[i]);

			count++;
			if (save == -1)
				save = i;

			continue ;
		}
		else
			closedir(directory);
	}

	if (save > 0)
		writeStr("\n", 1);

	if (count != 0 && infos->listing == false)
		writeStr("\n", 1);
}

void	list(tInfos* infos, char** paths, int value)
{
	DIR*		directory;
	char**		newPaths = NULL;

	for (int i = 0; paths[i] != NULL; i++)
	{
		if (paths[i][getStrLen(paths[i]) - 1] != '/')
			continue ;

		directory = opendir(paths[i]);
		if (directory == NULL)
		{
			printListError(paths[i]);
			
			if (value == true)
				return ;
			continue ;
		}

		if (value == true || i != 0)
			writeStr("\n", 1);

		if (getArrLen(paths) > 1 || infos->recursive == true || infos->title == true)
			writeStr(paths[i], 1), writeStr(":\n", 1);

		newPaths = getFolderElements(infos, directory, paths[i]);
		if (newPaths == NULL)
		{
			closedir(directory);
			if (value == true)
				return ;
			continue ;
		}

		if (infos->time == true)
			reOrderFolder(infos, &newPaths, paths[i]);
		printFolder(infos, directory, newPaths, paths[i]);

		if (infos->listing == false)
			writeStr("\n", 1);

		if (infos->recursive == true)
		{
			for (int k = 0; newPaths[k] != NULL; k++)
			{
				char*	name = getName(newPaths[k]);
				if (name != NULL && name[getStrLen(name) - 1] == '/')
					list(infos, newPaths + k, true);
			}
		}

		freeArray(newPaths);
		closedir(directory);

		if (value == true)
			return ;
	}
}
