#include "../../include/header.h"

char*	getDate(char* path)
{
	char*	date;
	char*	time;
	tStat	info;

	lstat(path, &info);

	time = ctime(&info.st_mtime);
	if (!time)
		{ systemFailed(); return ("NULL"); }

	int k = 0;
	while (time[k] != '\0' && time[k - 1] != ' ')
		k++;
	date = time + k;

	k = getStrLen(date) - 1;
	while (k != 0 && date[k] != ':')
		k--;
	date[k] = '\0';

	return (date);
}

char*	getSize(char* path)
{
	char*	size;
	tStat	info;

	lstat(path, &info);
	size = getNumber(info.st_size);

	return (size);
}

char*	getRight(int value, mode_t info)
{
	char*	str;
	int*	values;

	str = malloc(sizeof(char) * 4);
	if (!str)
		{ memoryFailed(); return (NULL); }

	values = malloc(sizeof(int) * 3);
	if (!values)
		{ free(str), memoryFailed(); return (NULL); }

	str[0] = '-', str[1] = '-', str[2] = '-';
	str[3] = '\0';

	if (value == 1)
		values[0] = S_IRUSR, values[1] = S_IWUSR, values[2] = S_IXUSR;
	if (value == 2)
		values[0] = S_IRGRP, values[1] = S_IWGRP, values[2] = S_IXGRP;
	if (value == 3)
		values[0] = S_IROTH, values[1] = S_IWOTH, values[2] = S_IXOTH;

	if (info & values[0])
		str[0] = 'r';
	if (info & values[1])
		str[1] = 'w';
	if (info & values[2])
		str[2] = 'x';

	free(values);

	return (str);
}

char*	getRights(char** data, tStat info)
{
	char*	value;
	char*	str;

	value = getRight(1, info.st_mode), str = *data;
	if (!value)
		return (NULL);
	*data = getJoin(*data, value, "\0");
	if (!*data)
		{ free(value); return (NULL); }
	free(value), free(str);

	value = getRight(2, info.st_mode), str = *data;
	if (!value)
		return (NULL);
	*data = getJoin(*data, value, "\0");
	if (!*data)
		{ free(value); return (NULL); }
	free(value), free(str);

	value = getRight(3, info.st_mode), str = *data;
	if (!value)
		return (NULL);
	*data = getJoin(*data, value, "\0");
	if (!*data)
		{ free(value); return (NULL); }
	free(value), free(str);

	return (*data);
}

char*	getOthers(char** data, tStat info)
{
	char*	value;
	char*	str;

	value = getNumber(info.st_nlink), str = *data;
	if (!value)
		return (NULL);
	*data = getJoin(*data, " ", value);
	if (!*data)
		{ free(value); return (NULL); }
	free(value), free(str);

	value = getpwuid(info.st_uid)->pw_name, str = *data;
	if (!value)
		return (NULL);
	*data = getJoin(*data, " ", value);
	if (!*data)
		{ memoryFailed(); return (NULL); }
	free(str);

	value = getgrgid(info.st_gid)->gr_name, str = *data;
	if (!value)
		return (NULL);
	*data = getJoin(*data, " ", value);
	if (!*data)
		{ memoryFailed(); return (NULL); }
	free(str);

	return (*data);
}

char*	getData(char* path)
{
	char*	data = NULL;
	tStat	info;

	lstat(path, &info);

	if (S_ISLNK(info.st_mode) == true)
		data = getDup("l");
	else if (S_ISDIR(info.st_mode) == true)
		data = getDup("d");

	if (S_ISLNK(info.st_mode) == false && S_ISDIR(info.st_mode) == false)
		data = getDup("-");

	if (!data)
		{ memoryFailed(); return (NULL); }

	if (getRights(&data, info) == NULL)
		{ memoryFailed(); return (NULL); }

	if (getOthers(&data, info) == NULL)
		{ memoryFailed(); return (NULL); }

	return (data);
}

char*	getLink(char* path)
{
	char*	str = NULL;
	tStat	info;

	lstat(path, &info);

	str = malloc(sizeof(char) * 5000);
	if (!str)
		{ memoryFailed(); return (NULL); }

	for (int i = 0; i != 5000; i++)
		str[i] = '\0';

	str[0] = '-', str[1] = '>', str[2] = ' ';

	if (readlink(path, str + 3, 4096) == -1)
		{ writeStr("\n", 2); printPathError(path); return (NULL); }

	return (str);
}
