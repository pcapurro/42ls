#include "../../include/header.h"

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
