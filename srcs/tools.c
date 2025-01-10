#include "../include/header.h"

void	memoryFailed(void)
{
	writeStr("Error! Memory allocation failed.\n", 2);
}

void	systemFailed(void)
{
	writeStr("Error! System failed.\n", 2);
}

void	addElement(char*** array, char* element)
{
	int		len = getArrLen(*array);
	char	**newArray = NULL;

	newArray = malloc(sizeof(char *) * (len + 2));
	if (!newArray || newArray == NULL)
		memoryFailed();
	else
	{
		for (int i = 0; i != len; i++)
			newArray[i] = (*array)[i];

		newArray[len + 1] = NULL;
		newArray[len] = element;

		if (*array != NULL)
			free(*array);
		*array = newArray;
	}
}
