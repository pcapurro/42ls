#include "../include/header.h"

void	setToDefault(tInfos* infos)
{
	infos->error = false;

	infos->paths = NULL;
	infos->options = false;

	infos->listing = false;
	infos->recursive = false;
	infos->hidden = false;
	infos->reverse = false;
	infos->time = false;
}

void	printHelp(void)
{
	writeStr("Usage: ./ft_ls [paths] [options]\n", 1);
	writeStr("Supported options: -l, -R, -a, -r and -t.\n", 1);
}

bool	isHelp(const char* str)
{
	if (getStrLen(str) != 6)
		return (false);

	if (str[0] == '-' && str[1] == '-' && str[2] == 'h' \
		&& str[3] == 'e' && str[4] == 'l' && str[5] == 'p')
		return (true);
	
	return (false);
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
		if (infos.error == true)
			return (1);

		getPaths(argv + 1, &infos);

		list(&infos, infos.paths);

		for (int i = 0; infos.paths[i] != NULL; i++)
			free(infos.paths[i]);
		free(infos.paths);

		if (infos.error == true)
			return (1);
	}

	return (0);
}

		// printf("paths: \n");
		// for (int i = 0; infos.paths[i] != NULL; i++)
		// 	printf("- '%s'\n", infos.paths[i]);
		// printf("\n");

		// printf("options: \n");
		// if (infos.options == false)
		// 	printf("none\n");
		// else
		// {
		// 	if (infos.listing == true)
		// 		printf("-l\n");
		// 	if (infos.recursive == true)
		// 		printf("-R\n");
		// 	if (infos.hidden == true)
		// 		printf("-a\n");
		// 	if (infos.reverse == true)
		// 		printf("-r\n");
		// 	if (infos.time == true)
		// 		printf("-t\n");
		// }