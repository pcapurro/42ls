#include "../include/header.h"

char	**initializeSubDirectory(const char* originalDir)
{
	char**	newElements = NULL;

	newElements = malloc(sizeof(char *) * 2);
	if (!newElements)
		{ memoryFailed(); return (NULL); }

	if (originalDir[getStrLen(originalDir) - 1] != '/')
		newElements[0] = getJoin(originalDir, "/", "\0");
	else
		newElements[0] = getDup(originalDir);
	newElements[1] = NULL;

	if (newElements[0] == NULL)
		return (NULL);

	return (newElements);
}

char	**getSubDirectories(const char* originalDir, tInfos* infos)
{
	char**			newElements = NULL;
	char*			path = NULL;
	DIR*			directory;
	struct dirent*	dirEntry;

	newElements = initializeSubDirectory(originalDir);
	if (!newElements)
		return (NULL);

	for (int i = 0; newElements[i] != NULL; i++)
	{
		directory = opendir(newElements[i]);
		if (directory == NULL)
			{ free(newElements), closedir(directory); return (NULL); }

		while (1)
		{
			dirEntry = readdir(directory);
			if (dirEntry == NULL)
				break ;

			path = getJoin(newElements[i], dirEntry->d_name, "/");
			if (!path)
				{ free(newElements), closedir(directory); return (NULL); }

			if (isFolder(dirEntry->d_name, path, infos) == true)
			{
				if (addElement(&newElements, path) == NULL)
					{ free(newElements), free(path); return (NULL); }
			}
			free(path);
		}
		closedir(directory);
	}

	return (newElements);
}

void	getRecursivePaths(tInfos* infos)
{
	const char*		element = NULL;
	char**			newPaths = NULL;
	char**			sequence = NULL;

	for (int i = 0; infos->paths[i] != NULL; i++)
	{
		element = infos->paths[i];
		sequence = getSubDirectories(element, infos);
		if (sequence == NULL || mergeElements(&newPaths, &sequence) == NULL)
			{ infos->error = true; break ; }
	}
	free(infos->paths);
	infos->paths = newPaths;
}

void	orderByTime(tInfos* infos, char ***array)
{
	int			len = getArrLen(*array);
	time_t		time = 0;
	char		**newPaths = NULL;

	newPaths = malloc(sizeof(char *) * (len + 1));
	if (!newPaths)
		{ memoryFailed(); infos->error = true; return ; }
	newPaths[len] = NULL;

	for (int k = 0, save = 0; k != len; k++, time = 0)
	{
		for (int i = 0; i != len; i++)
		{
			if ((*array)[i] != NULL)
			{
				struct stat	dirInfos;
				stat((*array)[i], &dirInfos);
				if (dirInfos.st_mtime > time)
					time = dirInfos.st_mtime, save = i;
			}
		}
		newPaths[k] = (*array)[save];
		(*array)[save] = NULL;
	}
	free(*array);
	*array = newPaths;
}

void	orderByAlph(tInfos* infos, char ***array)
{
	;
}

void	list(tInfos* infos)
{
	if (infos->recursive == true)
		getRecursivePaths(infos);

	if (infos->time == true)
		orderByTime(infos, &infos->paths);
	else
		orderByAlph(infos, &infos->paths);
}
