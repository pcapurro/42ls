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

void	freeArray(tInfos* infos)
{
	for (int i = 0; infos->paths[i] != NULL; i++)
		free(infos->paths[i]);
	free(infos->paths);
}

void	memoryFailed(void)
{
	writeStr("Error! Memory allocation failed.\n", 2);
}

void	systemFailed(void)
{
	writeStr("Error! System failed.\n", 2);
}
