#include "../include/header.h"

int	getElementInTimeOrder(char** array, const int pathsLen)
{
	int		save = 0;
	time_t	time = 0;
	tStat	dirInfos;

	if (pathsLen == 1)
		return (0);

	for (int i = 0; i != pathsLen; i++)
	{
		if (array[i] != NULL)
		{
			stat(array[i], &dirInfos);

			if (dirInfos.st_mtime > time)
				time = dirInfos.st_mtime, save = i;
		}
	}

	return (save);
}

int	getElementInAlphOrder(char** array, const int pathsLen)
{
	int		save = 0;
	int		count = 0;

	if (pathsLen == 1)
		return (0);

	for (int k = 0, value = 255; count != 1; k++, value = 255)
	{
		count = 0;
		for (int j = 0; j != pathsLen; j++)
		{
			if (array[j] != NULL && array[j][k] < value)
				value = array[j][k];
		}
		for (int j = 0; j != pathsLen; j++)
		{
			if (array[j] != NULL && array[j][k] == value)
				count++, save = j;
		}

		if (value == '\0')
			break ;
	}

	return (save);
}
