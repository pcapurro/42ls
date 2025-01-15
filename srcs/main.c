#include "../include/header.h"

void	setToDefault(tInfos* infos)
{
	infos->listing = false;
	infos->recursive = false;
	infos->hidden = false;
	infos->reverse = false;
	infos->time = false;

	infos->title = false;

	infos->paths = NULL;
	infos->options = false;

	infos->error = 0;
}

void	setToNull(tInfos* infos)
{
	for (int i = 0; infos->paths[i] != NULL; i++)
		free(infos->paths[i]);

	free(infos->paths);
	infos->paths = NULL;
}

int	main(const int argc, char** argv)
{	
	if (argc == 2 && isHelp(argv[1]) == true)
		printHelp();
	else
	{
		tInfos	infos;

		setToDefault(&infos);

		getOptions(argv + 1, &infos);
		if (infos.error != 0)
			return (infos.error);

		getPaths(argv + 1, &infos);

		preList(&infos);
		list(&infos, infos.paths, false);

		setToNull(&infos);

		if (infos.error != 0)
			return (infos.error);
	}

	return (0);
}
