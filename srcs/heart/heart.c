#include "../../include/header.h"

void	preList(tInfos* infos)
{
	int		count = 0;
	int		save = -1;
	DIR*	directory;

	for (int i = 0; infos->paths[i] != NULL; i++)
	{
		if (infos->paths[i][getStrLen(infos->paths[i]) - 1] == '/')
			continue ;

		directory = opendir(infos->paths[i]);
		if (directory == NULL)
		{
			printElement(infos, infos->paths[i], true);
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

void	listRecursive(tInfos* infos, char** paths)
{
	char*	name;

	for (int k = 0; paths[k] != NULL; k++)
	{
		name = getName(paths[k]);
		if (name != NULL && name[getStrLen(name) - 1] == '/')
			list(infos, paths + k, true);
		
		if (infos->error == 1)
			break ;
	}
}

void	list(tInfos* infos, char** paths, int value)
{
	DIR*		directory = NULL;
	char**		newPaths = NULL;

	if (infos->error == 1)
		return ;

	for (int i = 0; paths[i] != NULL; i++)
	{
		if (paths[i][getStrLen(paths[i]) - 1] != '/')
			continue ;

		directory = opendir(paths[i]);
		if (directory == NULL && value == true)
			{ printPathError(paths[i]), infos->error = 2; return ; }
		if (directory == NULL && value == false)
			{ printPathError(paths[i]), infos->error = 2; continue ; }

		newPaths = getFolderElements(infos, directory, paths[i]);
		if (newPaths == NULL)
		{
			if (value == true || infos->error == 1)
				return ;
			continue ;
		}

		if (value == true || i != 0)
			writeStr("\n", 1);
		printFolder(infos, newPaths, paths + i);

		if (infos->recursive == true)
			listRecursive(infos, newPaths);

		freeArray(newPaths);

		if (value == true || infos->error == 1)
			return ;
	}
}
