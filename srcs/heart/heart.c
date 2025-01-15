#include "../../include/header.h"

void	preList(tInfos* infos)
{
	int		count = 0;
	int		save = -1;
	DIR*	directory;

	for (int i = 0; infos->paths[i] != NULL; i++)
	{
		directory = opendir(infos->paths[i]);
		if (directory == NULL)
		{
			printElement(infos, infos->paths[i]);
			if (infos->error == 1)
				return ;

			count++;
			if (save == -1)
				save = i;

			continue ;
		}
		else
			closedir(directory);
	}

	if (save > 0)
		writeStr("\n", 1);

	if (count != 0 && infos->listing == false)
		writeStr("\n", 1);
}

void	list(tInfos* infos, char** paths, int value)
{
	DIR*		directory;
	char**		newPaths = NULL;

	if (infos->error == 1)
		return ;

	for (int i = 0; paths[i] != NULL; i++)
	{
		if (paths[i][getStrLen(paths[i]) - 1] != '/')
			continue ;

		directory = opendir(paths[i]);
		if (directory == NULL)
		{
			printPathError(paths[i]);
			infos->error = 2;

			if (value == true)
				return ;
			continue ;
		}

		if (value == true || i != 0)
			writeStr("\n", 1);

		if (getArrLen(paths) > 1 || infos->recursive == true || infos->title == true)
			writeStr(paths[i], 1), writeStr(":\n", 1);

		newPaths = getFolderElements(infos, directory, paths[i]);
		if (newPaths == NULL)
		{
			closedir(directory);
			if (value == true || infos->error == 1)
				return ;
			continue ;
		}

		if (infos->time == true)
			reOrderFolder(infos, &newPaths, paths[i]);
		printFolder(infos, newPaths, paths[i]);

		if (infos->listing == false)
			writeStr("\n", 1);

		if (infos->recursive == true)
		{
			for (int k = 0; newPaths[k] != NULL; k++)
			{
				char*	name = getName(newPaths[k]);
				if (name != NULL && name[getStrLen(name) - 1] == '/')
					list(infos, newPaths + k, true);
				
				if (infos->error == 1)
					break ;
			}
		}

		freeArray(newPaths);
		closedir(directory);

		if (value == true || infos->error == 1)
			return ;
	}
}
