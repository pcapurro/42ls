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

bool	isFolder(const char* name, const char* path)
{
	if (name[0] == '.' && name[1] == '\0')
		return (false);
	if (name[0] == '.' && name[1] == '.' && name[2] == '\0')
		return (false);

	struct stat		dirInfos;

	stat(path, &dirInfos);
	if (S_ISDIR(dirInfos.st_mode) == false)
		return (false);

	return (true);
}

void	searchForExtraPaths(const char** paths, tInfos* infos)
{
	DIR				*directory;
	struct dirent	*dirEntry;

	const char		*element = NULL;
	char			*path = NULL;
	char			**newPaths = NULL;
	char			**newElements = NULL;

	for (int i = 0; paths[i] != NULL; i++)
	{
		element = paths[i];
		if (addElement(&newPaths, element) == NULL)
			{ infos->error = true; break ; }

		if (infos->recursive == true)
		{
			printf("opening : '%s'\n", element);
			directory = opendir(element);
			if (directory == NULL)
				{ infos->error = true; break ; }

			while (1)
			{
				dirEntry = readdir(directory);
				if (dirEntry == NULL)
					break ;

				path = getJoin(element, dirEntry->d_name);
				if (isFolder(dirEntry->d_name, path) == true)
				{
					if (addElement(&newElements, path) == NULL)
						{ infos->error = true; break ; }
				}
				free(path);
			}

			closedir(directory);
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
