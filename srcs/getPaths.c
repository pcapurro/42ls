#include "../include/header.h"

void	searchForPaths(char** argv, tInfos* infos)
{
	for (int i = 0, j = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] == '\0' || \
			(argv[i][0] == '-' && argv[i][1] != '\0'))
			continue ;
		
		int		value = 0;
		tStat	pathInfos;
		DIR*	directory = NULL;

		directory = opendir(argv[i]);
		value = lstat(argv[i], &pathInfos);

		if (directory == NULL && value != 0)
			printListError(argv[i]);
		else
		{
			if (S_ISDIR(pathInfos.st_mode) == true && argv[i][getStrLen(argv[i]) - 1] != '/')
				infos->paths[j] = getJoin(argv[i], "/", "\0");
			else
				infos->paths[j] = getDup(argv[i]);

			if (!infos->paths[j])
				{ infos->error = true; return ; }
			j++;
		}

		if (directory != NULL)
			closedir(directory);
	}
}

void	getPaths(char** argv, tInfos* infos)
{
	int	len = 0;

	for (int i = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] != '\0' \
			&& (argv[i][0] != '-' || argv[i][1] == '\0'))
			len++;
	}

	if (len > 1)
		infos->title = true;

	if (len == 0)
		infos->paths = malloc(sizeof(const char *) * 2);
	else
	{
		infos->paths = malloc(sizeof(const char *) * (len + 1));
		for (int i = 0; i != len + 1; i++)
			infos->paths[i] = NULL;
	}

	if (!infos->paths)
	{
		infos->error = true;
		infos->paths = NULL;
		memoryFailed();

		return ;
	}

	if (len == 0)
		infos->paths[0] = getDup("./"), len++;
	else
		searchForPaths(argv, infos);
	infos->paths[len] = NULL;
}
