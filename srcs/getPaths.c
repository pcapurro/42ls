#include "../include/header.h"

void	searchForPaths(char** argv, tInfos* infos)
{
	for (int i = 0, j = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] == '\0' || \
			(argv[i][0] == '-' && argv[i][1] != '\0'))
			continue ;

		infos->paths[j] = getDup(argv[i]);
		if (!infos->paths[j])
			{ infos->error = true; return ; }
		j++;
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

	if (len == 0)
		infos->paths = malloc(sizeof(const char *) * 2);
	else
		infos->paths = malloc(sizeof(const char *) * (len + 1));

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
