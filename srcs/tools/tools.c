#include "../../include/header.h"

void*	addElement(char*** array, const char* element)
{
	int		len = getArrLen(*array);
	char	**newArray = NULL;

	newArray = malloc(sizeof(char *) * (len + 2));
	if (!newArray)
		return (NULL);
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
		{
			newArray[len] = NULL;
			return (NULL);
		}
	}

	return (newArray);
}

char**	copyArray(char** array, const int value)
{
	char**	newArray = NULL;

	newArray = malloc(sizeof(char*) * (getArrLen(array) + 1));
	if (!newArray)
		return (NULL);

	if (value == 0)
	{
		for (int i = 0; array[i] != NULL; i++)
			newArray[i] = array[i];
	}
	else
	{
		for (int i = 0; array[i] != NULL; i++)
		{
			newArray[i] = getDup(array[i]);
			if (!newArray[i])
			{
				i--;
				while (i != -1)
					free(newArray[i]), i--;
				free(newArray);

				return (NULL);
			}
		}
	}
	newArray[getArrLen(array)] = NULL;

	return (newArray);
}

void*	findElement(char** array, char* element)
{
	if (array == NULL)
		return (NULL);

	for (int i = 0; array[i] != NULL; i++)
	{
		if (isSame(array[i], element) == true)
			return (array[i]);
	}

	return (NULL);
}

void	freeArray(char** array)
{
	if (array != NULL)
	{
		for (int i = 0; array[i] != NULL; i++)
			free(array[i]);
		free(array);
	}
}

char*	getName(char* path)
{
	int		i = 0;
	char*	name;

	while (path[i] != '\0')
		i++;
	i--;
	if (path[i] == '/')
		i--;

	while (i != 0 && path[i] != '/')
		i--;

	name = path + i;
	if (name[0] == '/' && name[1] != '\0')
		name += 1;

	if (isSame("./", name) == true || isSame("../", name) == true)
		return (NULL);

	return (name);
}
