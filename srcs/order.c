#include "../include/header.h"

void	orderByTime(tInfos* infos, char*** array)
{
	int			len = getArrLen(*array);
	time_t		time = 0;
	char		**newPaths = NULL;

	newPaths = malloc(sizeof(char *) * (len + 1));
	if (!newPaths)
		{ memoryFailed(); infos->error = true; return ; }
	newPaths[len] = NULL;

	for (int k = 0, save = 0; k != len; k++, time = 0)
	{
		for (int i = 0; i != len; i++)
		{
			if ((*array)[i] != NULL)
			{
				struct stat	dirInfos;
				stat((*array)[i], &dirInfos);
				if (dirInfos.st_mtime > time)
					time = dirInfos.st_mtime, save = i;
			}
		}
		newPaths[k] = (*array)[save];
		(*array)[save] = NULL;
	}
	free(*array);
	*array = newPaths;
}

void	orderByAlph(tInfos* infos, char*** array)
{
	char**	newArray = NULL;
	char*	element = NULL;

	for (int i = 0, save = 0; (*array)[i] != NULL; i++, save = 0)
	{
		int count = 0;
		for (int k = 0, value = 127; count != 1; k++, value = 127)
		{
			count = 0;
			for (int i = 0; (*array)[i] != NULL; i++)
			{
				if (findElement(newArray, (*array)[i]) == NULL && (*array)[i][k] < value)
					value = (*array)[i][k];
			}
			for (int i = 0; (*array)[i] != NULL; i++)
			{
				if (findElement(newArray, (*array)[i]) == NULL && (*array)[i][k] == value)
					count++, save = i;
			}
		}
		element = (*array)[save];
		addElement(&newArray, element);
	}
	freeArray(array);
	*array = newArray;
}
