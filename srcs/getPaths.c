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

void	searchForExtraPaths(const char** paths, tInfos* infos)
{
	char	**newPaths = NULL;

	// for (int i = 0; paths[i] != NULL; i++)
	// 	// ...
	// free(paths);
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

	if (!paths || paths == NULL)
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
