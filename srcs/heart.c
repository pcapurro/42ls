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
	char**		newElements = NULL;
	char*		path = NULL;
	DIR*		directory;
	t_dirent*	dirEntry;

	newElements = initializeSubDirectory(originalDir);
	if (!newElements)
		return (NULL);

	for (int i = 0; newElements[i] != NULL; i++)
	{
		directory = opendir(newElements[i]);
		if (directory == NULL)
			continue ;

		while (1)
		{
			dirEntry = readdir(directory);
			if (dirEntry == NULL)
				break ;

			path = getJoin(newElements[i], dirEntry->d_name, "/");
			if (!path)
				{ free(newElements), closedir(directory); return (NULL); }

			if (isFolder(dirEntry->d_name, dirEntry->d_type, infos) == true)
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

void	listRecursively(tInfos* infos)
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

void	printListError(const char* element)
{
	writeStr("ft_ls: unable to access '", 2);
	writeStr(element, 2);
	writeStr("': ", 2);

	perror("");
}

void	printElement(tInfos* infos, t_dirent* dirEntry)
{
	if (dirEntry->d_type == DT_DIR)
	{
		writeStr("\033[1m", 1);
		writeStr("\033[34m", 1);
		writeStr(dirEntry->d_name, 1);
		writeStr("\033[0m", 1);
	}
	else
		writeStr(dirEntry->d_name, 1);

	if (infos->listing == false)
		writeStr("  ", 1);
	else
		writeStr("\n", 1);
}

void	list(tInfos* infos)
{
	DIR*		directory;
	t_dirent*	dirEntry;

	for (int i = 0; infos->paths[i] != NULL; i++)
	{
		directory = opendir(infos->paths[i]);
		if (directory == NULL)
			{ printListError(infos->paths[i]); continue ; }

		if (getArrLen(infos->paths) > 1)
			writeStr(infos->paths[i], 1), writeStr(":\n", 1);

		while (1)
		{
			dirEntry = readdir(directory);
			if (dirEntry == NULL)
				break ;
			
			if (infos->hidden == false \
				&& dirEntry->d_name[0] == '.')
				continue ;

			printElement(infos, dirEntry);
		}

		if (infos->listing == false)
			writeStr("\n", 1);
		if (getArrLen(infos->paths) > 1 && infos->paths[i + 1] != NULL)
			writeStr("\n", 1);
	}
}
