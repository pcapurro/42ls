#include "../include/header.h"

void	memoryFailed(void)
{
	writeStr("Error! Memory allocation failed.\n", 2);
}

void	systemFailed(void)
{
	writeStr("Error! System failed.\n", 2);
}

void	freeArray(char** array)
{
	for (int i = 0; array != NULL && array[i] != NULL; i++)
		free(array[i]);
	free(array);
}

void	*mergeElements(char*** array1, char*** array2)
{
	int		i = 0;
	int		len = getArrLen(*array1) + getArrLen(*array2);
	char	**newArray = NULL;

	newArray = malloc(sizeof(char *) * (len + 1));
	if (!newArray)
		memoryFailed();
	else
	{
		if (*array1 != NULL)
		{
			for (int k = 0; (*array1)[k] != NULL; k++, i++)
				newArray[i] = (*array1)[k];
		}
		for (int k = 0; (*array2)[k] != NULL; k++, i++)
			newArray[i] = (*array2)[k];

		newArray[len] = NULL;

		free(*array1);
		*array1 = newArray;
		free(*array2);
		*array2 = NULL;
	}

	return (newArray);
}

void	*addElement(char*** array, const char* element)
{
	int		len = getArrLen(*array);
	char	**newArray = NULL;

	newArray = malloc(sizeof(char *) * (len + 2));
	if (!newArray)
		memoryFailed();
	else
	{
		for (int i = 0; i != len; i++)
			newArray[i] = (*array)[i];

		newArray[len + 1] = NULL;
		newArray[len] = getDup(element);

		if (*array != NULL)
			free(*array);
		*array = newArray;

		if (!newArray[len])
			{ memoryFailed(); return (NULL); }
	}

	return (newArray);
}
