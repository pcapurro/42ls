#include "../../include/header.h"

void	freeFolderElements(char** newElements, char* element)
{
	for (int i = 0; newElements[i] != NULL; i++)
		free(newElements[i]);
	free(newElements), newElements = NULL;
	if (element != NULL)
		free(element);
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

		if (infos->hidden == false && dirEntry->d_name[0] == '.')
			continue ;

		if (dirEntry->d_type == DT_DIR)
			element = getJoin(originalPath, dirEntry->d_name, "/");
		else
			element = getJoin(originalPath, dirEntry->d_name, "\0");

		if (element == NULL || addElement(&newElements, element) == NULL)
		{
			memoryFailed();
			infos->error = 1;
			freeFolderElements(newElements, element);
			break ;
		}
		free(element);
		element = NULL;
	}
	closedir(directory);

	if (newElements != NULL && infos->time == true)
		reOrderFolder(infos, &newElements, originalPath);

	return (newElements);
}

void	reOrderFolder(tInfos* infos, char*** paths, char* originalPath)
{
	int		pathsNumber = getArrLen(*paths);
	int		pathLen = getStrLen(originalPath);
	char**	newPaths = copyArray(*paths, 0);
	char**	otherPaths = NULL;

	if (!newPaths)
		{ infos->error = 1; return ; }

	otherPaths = copyArray(*paths, 1);
	if (!newPaths)
		{infos->error = 1; free(newPaths); return ; }
	
	for (int i = 0, end = 0; otherPaths[i] != NULL; i++)
	{
		end = getStrLen(otherPaths[i]) - 1;
		if (otherPaths[i][end] == '/')
			otherPaths[i][end] = '\0';
	}

	for (int i = 0, element = 0; i != pathsNumber; i++)
	{
		element = getElementInAlphOrder(otherPaths, pathsNumber, pathLen, infos->reverse);
		newPaths[i] = (*paths)[element];

		free(otherPaths[element]);
		otherPaths[element] = NULL;
	}

	free(otherPaths);
	free(*paths);
	*paths = newPaths;
}
