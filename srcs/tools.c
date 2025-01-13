#include "../include/header.h"

bool	isFolder(const char* name, const unsigned type, tInfos* infos)
{
	if (getStrLen(name) == 1 \
		&& name[0] == '.' && name[1] == '\0')
		return (false);

	if (getStrLen(name) == 2 \
		&& name[0] == '.' && name[1] == '.' && name[2] == '\0')
		return (false);

	if (name[0] == '.' && infos->hidden == false)
		return (false);

	if (type != DT_DIR)
		return (false);

	return (true);
}

bool	isSame(char* str1, const char* str2)
{
	if (getStrLen(str1) != getStrLen(str2))
		return (false);

	for (int i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i] != str2[i])
			return (false);
	}

	return (true);
}

void*	addElement(char*** array, const char* element)
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

void	memoryFailed(void)
{
	writeStr("Error! Memory allocation failed.\n", 2);
}

void	systemFailed(void)
{
	writeStr("Error! System failed.\n", 2);
}
