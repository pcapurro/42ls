#include "../include/header.h"

void	searchForPaths(const char** argv, const char** paths)
{
	for (int i = 0, j = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] == '\0' || \
			(argv[i][0] == '-' && argv[i][1] != '\0'))
			continue ;

		paths[j] = argv[i];
		j++;
	}
}

bool	isFolder(const char* name, const char* path, tInfos* infos)
{
	if (getStrLen(name) == 1 \
		&& name[0] == '.' && name[1] == '\0')
		return (false);

	if (getStrLen(name) == 2 \
		&& name[0] == '.' && name[1] == '.' && name[2] == '\0')
		return (false);

	if (name[0] == '.' && infos->hidden == false)
		return (false);

	struct stat	dirInfos;
	if (stat(path, &dirInfos) == -1)
		return (false);

	if (S_ISDIR(dirInfos.st_mode) == false)
		return (false);

	return (true);
}

bool	isSame(char* str1, const char* str2)
{
	if (getStrLen(str1) != getStrLen(str2))
		return (false);

	for (int i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i] != str2[i])
			return (false);
	}

	return (true);
}

void	*findElement(char** paths, const char* element)
{
	for (int i = 0; paths[i] != NULL; i++)
	{
		if (isSame(paths[i], element) == true)
			return (paths);
	}

	return (NULL);
}

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

void	searchForExtraPaths(const char** paths, tInfos* infos)
{
	const char*		element = NULL;
	char**			newPaths = NULL;
	char**			sequence = NULL;

	for (int i = 0; paths[i] != NULL; i++)
	{
		element = paths[i];
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
	infos->paths = newPaths;
	free(paths);
}

void	getPaths(const char** argv, tInfos* infos)
{
	int				len = 0;
	const char**	paths = NULL;

	for (int i = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] != '\0' \
			&& (argv[i][0] != '-' || argv[i][1] == '\0'))
			len++;
	}

	if (len == 0)
		paths = malloc(sizeof(const char *) * 2);
	else
		paths = malloc(sizeof(const char *) * (len + 1));

	if (!paths)
	{
		infos->error = true;
		paths = NULL;
		memoryFailed();

		return ;
	}

	if (len == 0)
		paths[0] = "./", len++;
	else
		searchForPaths(argv, paths);
	paths[len] = NULL;

	searchForExtraPaths(paths, infos);
}
