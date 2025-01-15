#include "../../include/header.h"

void	searchForPaths(char** argv, tInfos* infos)
{
	int		value = 0;
	tStat	pathInfos;
	DIR*	directory = NULL;

	for (int i = 0, j = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] == '\0' || \
			(argv[i][0] == '-' && argv[i][1] != '\0'))
			continue ;

		directory = opendir(argv[i]);
		value = lstat(argv[i], &pathInfos);

		if (directory == NULL && value != 0)
			printPathError(argv[i]), infos->error = 2;
		else
		{
			if (S_ISDIR(pathInfos.st_mode) == true && argv[i][getStrLen(argv[i]) - 1] != '/')
				infos->paths[j] = getJoin(argv[i], "/", "\0");
			else
				infos->paths[j] = getDup(argv[i]);

			if (!infos->paths[j])
			{
				memoryFailed();
				infos->error = 1;
				j--;
				while (j != -1)
					free(infos->paths[j]), j--;
				free(infos->paths);
				infos->paths = NULL;
				return ;
			}
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
		infos->paths = malloc(sizeof(const char *) * (len + 1));

	if (!infos->paths)
	{
		memoryFailed();
		infos->error = 1;
		infos->paths = NULL;

		return ;
	}

	if (len == 0)
	{
		infos->paths[0] = getDup("./"), len++;
		if (!infos->paths[0])
		{
			memoryFailed();
			infos->error = 1;

			free(infos->paths);
			infos->paths = NULL;
		}
	}
	else
	{
		for (int i = 0; i != len + 1; i++)
			infos->paths[i] = NULL;
		searchForPaths(argv, infos);
	}

	if (infos->paths != NULL)
		infos->paths[len] = NULL;
}
