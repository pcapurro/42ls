#include "../include/header.h"

char	**getSubDirectories(const char* originalDir, tInfos* infos)
{
	char**			newElements = NULL;
	char*			path = NULL;
	DIR*			directory;
	struct dirent*	dirEntry;

	if (addElement(&newElements, originalDir) == NULL)
	{
		if (newElements != NULL)
			free(newElements);
		return (NULL);
	}

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
		if (infos->recursive == true)
		{
			sequence = getSubDirectories(element, infos);
			if (sequence == NULL || mergeElements(&newPaths, &sequence) == NULL)
				{ infos->error = true; break ; }
		}
		else
		{
			if (addElement(&newPaths, element) == NULL)
				{ infos->error = true; break ; }
		}
	}
	free(infos->paths);
	infos->paths = newPaths;
}

void	list(tInfos *infos)
{
	if (infos->recursive == true)
		getRecursivePaths(infos);
}
