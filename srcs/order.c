#include "../include/header.h"

int	getElementInTimeOrder(char** array, int pathsNumber, int pathsLen)
{
	int		save = 0;
	int		count = 0;
	time_t	time = 0;
	tStat	dirInfos;

	if (pathsNumber == 1)
		return (0);

	for (int i = 0; i != pathsNumber; i++)
	{
		if (array[i] != NULL)
			save = i, count++;
	}

	if (count == 1)
		return (save);

	for (int i = 0; i != pathsNumber; i++)
	{
		if (array[i] != NULL)
		{
			stat(array[i] + pathsLen, &dirInfos);

			if (dirInfos.st_mtime > time)
				time = dirInfos.st_mtime, save = i;
		}
	}

	return (save);
}

int	getElementInAlphOrder(char** array, int pathsNumber, int pathsLen)
{
	int		save = 0;
	int		count = 0;

	if (pathsNumber == 1)
		return (0);

	for (int i = 0; i != pathsNumber; i++)
	{
		if (array[i] != NULL)
			save = i, count++;
	}

	if (count == 1)
		return (save);

	for (int k = 0, value = 255; count != 1; k++, value = 255)
	{
		count = 0;
		for (int j = 0; j != pathsNumber; j++)
		{
			if (array[j] != NULL && array[j][pathsLen + k] < value)
				value = array[j][pathsLen + k];
		}
		for (int j = 0; j != pathsNumber; j++)
		{
			if (array[j] != NULL && array[j][pathsLen + k] == value)
				count++, save = j;
		}

		if (value == '\0')
			break ;
	}

	return (save);
}
