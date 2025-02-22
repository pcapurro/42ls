#include "../../include/header.h"

bool	isValidOption(const char* str)
{
	if (getStrLen(str) == 0)
		return (false);

	for (int i = 0; str[i] != '\0'; i++)
	{	
		if (str[i] != 'l' && str[i] != 'R' && str[i] != 'a' \
			&& str[i] != 'r' && str[i] != 't')
			return (false);
	}

	return (true);
}

void	getOption(char* argv, tInfos* infos)
{
	char	option;

	if (infos->options == false)
		infos->options = true;

	for (int i = 0; argv[i] != '\0'; i++)
	{
		option = argv[i];

		if (option == 'l' && infos->listing == false)
			infos->listing = true;
		if (option == 'R' && infos->recursive == false)
			infos->recursive = true, infos->title = true;
		if (option == 'a' && infos->hidden == false)
			infos->hidden = true;
		if (option == 'r' && infos->reverse == false)
			infos->reverse = true;
		if (option == 't' && infos->time == false)
			infos->time = true;
	}
}

void	getOptions(char** argv, tInfos* infos)
{
	for (int i = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] == '\0' || argv[i][0] != '-' \
			|| (argv[i][0] == '-' && argv[i][1] == '\0'))
			continue ;
		
		if (isValidOption(argv[i] + 1) == false)
		{
			infos->error = 2;
			if (getStrLen(argv[i]) > 2 && argv[i][0] == '-' && argv[i][1] == '-')
				printOptionsError(0, argv[i]);
			else
				printOptionsError(1, argv[i] + 1);
			
			return ;
		}
		else
			getOption(argv[i], infos);
	}
}
