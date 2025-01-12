#include "../include/header.h"

void	printListError(const char* element)
{
	writeStr("ft_ls: unable to access '", 2);
	writeStr(element, 2);
	writeStr("': ", 2);

	perror("");
}

void	printElement(tInfos* infos, char* path)
{
	int i = getStrLen(path) - 1;

	if (path[i] == '/' && i != 0)
		i--;
	while (i != 0 && path[i] != '/')
		i--;

	char* name = path + i;
	if (i != 0)
		name = name + 1;

	writeStr(name, 1);

	if (infos->listing == false)
		writeStr("  ", 1);
	else
		writeStr("\n", 1);
}

void	list(tInfos* infos, char** paths)
{
	DIR*		directory;
	t_dirent*	dirEntry;
	char**		newPaths = NULL;
	char*		element = NULL;

	for (int i = 0; paths[i] != NULL; i++)
	{
		directory = opendir(paths[i]);
		if (directory == NULL)
			{ printListError(paths[i]); continue ; }

		if (getArrLen(paths) > 1 || infos->recursive == true)
			writeStr(paths[i], 1), writeStr(":\n", 1);

		while (1)
		{
			dirEntry = readdir(directory);
			if (dirEntry == NULL)
				break ;

			if (infos->hidden == false \
				&& dirEntry->d_name[0] == '.')
				continue ;

			if (dirEntry->d_type == DT_DIR)
				element = getJoin(paths[i], dirEntry->d_name, "/");
			else
				element = getJoin(paths[i], dirEntry->d_name, "\0");
			addElement(&newPaths, element);
		}

		if (newPaths == NULL)
			{ printf("\n"); continue ; }

		if (infos->time == true)
			orderByTime(infos, &newPaths);
		else
			orderByAlph(infos, &newPaths);

		for (int k = 0; newPaths[k] != NULL; k++)
			printElement(infos, newPaths[k]);
		printf("\n\n");

		if (infos->recursive == true)
		{
			for (int k = 0; newPaths[k] != NULL; k++)
			{
				if (newPaths[k][getStrLen(newPaths[k]) - 1] == '/')
					list(infos, newPaths + k);
			}
		}
		newPaths = NULL;

		if (infos->recursive == true \
			&& paths[i][getStrLen(paths[i]) - 1] == '/')
			return ;

		if (infos->listing == false)
			writeStr("\n", 1);
		if (getArrLen(paths) > 1 && paths[i + 1] != NULL)
			writeStr("\n", 1);
	}
}
