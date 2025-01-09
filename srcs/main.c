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

bool	isHelp(const char *str)
{
	if (str[0] == '-' && str[1] == '-' && str[2] == 'h'
		&& str[3] == 'e' && str[4] == 'l' && str[5] == 'p')
		return (true);
	
	return (false);
}

int	main(const int argc, const char** argv)
{
	tInfos	infos;

	setToDefault(&infos);
	if (argc > 1)
	{
		if (argc == 2 && isHelp(argv[1]) == true)
			{ printHelp(); return (0); }

		getOptions(argv + 1, &infos);
		getPaths(argv + 1, &infos);

		if (infos.error == true)
			return (1);
	}

	return (0);
}

	// printf("paths: \n");
	// if (infos.paths == NULL)
	// 	printf(".\n\n");
	// else
	// {
	// 	for (int i = 0; infos.paths[i] != NULL; i++)
	// 		printf("- '%s'\n", infos.paths[i]);
	// 	printf("\n");
	// }

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