#include "../include/header.h"

int	getElementInTimeOrder(char** array, int pathsNumber, bool reverse)
{
	int		save = 0;
	int		count = 0;
	time_t	time;
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

	if (reverse == true)
		time = 2147483647;
	else
		time = 0;

	for (int i = 0; i != pathsNumber; i++)
	{
		if (array[i] != NULL)
		{
			stat(array[i], &dirInfos);

			if (reverse == true && dirInfos.st_mtime < time)
				time = dirInfos.st_mtime, save = i;
			if (reverse == false && dirInfos.st_mtime > time)
				time = dirInfos.st_mtime, save = i;
		}
	}

	return (save);
}

int	getElementInAlphOrder(char** array, int pathsNumber, int pathsLen, bool reverse)
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
			{
				value = array[j][pathsLen + k];
				save = j;
				count = 0;
			}

			if (array[j] != NULL && array[j][pathsLen + k] == value)
				count++;
		}

		if (value == '\0')
			break ;
	}

	return (save);
}
