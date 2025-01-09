#include "../include/header.h"

void	searchForPaths(const char** argv, tInfos* infos)
{
	for (int i = 0, j = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] == '\0' || \
			(argv[i][0] == '-' && argv[i][1] != '\0'))
			continue ;

		infos->paths[j] = getDup(argv[i]);
		if (!infos->paths[j] || infos->paths[j] == NULL)
		{
			infos->error = true;
			memoryFailed();
			for (int k = j - 1; k != -1; k--)
				free(infos->paths[k]);
			free(infos->paths);
			infos->paths = NULL;

			return ;
		}
		j++;
	}
}

void	getPaths(const char** argv, tInfos* infos)
{
	int len = 0;

	for (int i = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] != '\0' \
			&& (argv[i][0] != '-' || argv[i][1] == '\0'))
			len++;
	}

	infos->paths = NULL;
	if (len == 0)
		return ;

	infos->paths = malloc(sizeof(char *) * (len + 1));
	if (!infos->paths || infos->paths == NULL)
	{
		infos->error = true;
		infos->paths = NULL;
		memoryFailed();

		return ;
	}
	else
	{
		infos->paths[len] = NULL;
		searchForPaths(argv, infos);
	}
}
