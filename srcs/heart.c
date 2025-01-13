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
	int i = getStrLen(path) - 1;

	if (path[i] == '/' && i != 0)
		i--;
	while (i != 0 && path[i] != '/')
		i--;

	char* name = path + i;
	if (i != 0)
		name = name + 1;

	writeStr(name, 1);

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

void	printFolder(tInfos* infos, char** paths)
{
	int		len = getArrLen(paths);
	char**	newArray;

	newArray = malloc(sizeof(char*) * (len + 1));
	if (!newArray)
		return ;
	for (int i = 0; paths[i] != NULL; i++)
		newArray[i] = paths[i];
	newArray[len] = NULL;

	for (int count = 0, element = 0; count != len; count++)
	{
		if (infos->time == true)
			element = getElementInTimeOrder(newArray, len);
		else
			element = getElementInAlphOrder(newArray, len);

		if (element != -1)
			printElement(infos, newArray[element]);

		newArray[element] = NULL;
	}

	writeStr("\n", 1);
}

void	list(tInfos* infos, char** paths, int value)
{
	DIR*		directory;
	char**		newPaths = NULL;

	if (infos->recursive == true && value == true)
		writeStr("\n", 1);

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

		if (getArrLen(paths) > 1 || infos->recursive == true)
			writeStr(paths[i], 1), writeStr(":\n", 1);

		newPaths = getFolderElements(infos, directory, paths[i]);
		if (newPaths == NULL)
		{
			closedir(directory);
			if (value == true)
				return ;
			continue ;
		}

		printFolder(infos, newPaths);

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
