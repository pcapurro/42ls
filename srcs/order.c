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

char*	getTopOrder(char **array)
{
	if (getArrLen(array) == 1)
		return (array[0]);

	int	value;
	int count = 0, save = 0;

	for (int k = 0; count != 1; k++)
	{
		value = 127;
		count = 0;
		for (int i = 0; array[i] != NULL; i++)
		{
			if (array[i][k] < value)
				value = array[i][k];
		}
		for (int i = 0; array[i] != NULL; i++)
		{
			if (array[i][k] == value)
				count++, save = i;
		}
	}

	return (array[save]);
}

void	orderByAlph(tInfos* infos, char*** array)
{
	int			len = getArrLen(*array);
	char**		newArray = NULL;
	char**		orderedArray = NULL;

	newArray = malloc(sizeof(char *) * (len + 1));
	if (!newArray)
		{ memoryFailed(); infos->error = true; return ; }
	for (int i = 0; i != len; i++)
		newArray[i] = NULL;
	newArray[len] = NULL;

	for (int value = 127; getArrLen(newArray) != len;)
	{
		orderedArray = malloc(sizeof(char *) * (len + 1));
		if (!orderedArray)
			{ memoryFailed(); infos->error = true; return ; }
		for (int i = 0; i != len; i++)
			orderedArray[i] = NULL;
		orderedArray[len] = NULL;

		for (int i = 0; i != len; i++)
		{
			if ((*array)[i] != NULL && (*array)[i][0] < value)
				value = (*array)[i][0];
		}
		for (int i = 0, k = 0; i != len; i++, k = 0)
		{
			if ((*array)[i] != NULL && (*array)[i][0] == value)
			{
				while (orderedArray[k] != NULL)
					k++;
				orderedArray[k] = (*array)[i];
			}
		}

		char* element = getTopOrder(orderedArray);
		for (int i = 0; i != len; i++)
		{
			if (newArray[i] == NULL)
				{ newArray[i] = element ; break; };
		}
		for (int i = 0; i != len; i++)
		{
			if ((*array)[i] != NULL && element == (*array)[i])
				(*array)[i] = NULL;
		}
		orderedArray = NULL;
	}
	*array = newArray;
}
