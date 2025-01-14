#include "../include/header.h"

char*	getDate(char* path)
{
	char*	date;
	char*	time;
	tStat	info;

	lstat(path, &info);

	time = ctime(&info.st_mtime);
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
		return (NULL);

	values = malloc(sizeof(int) * 3);
	if (!values)
		return (NULL);

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

char*	getData(char* path)
{
	char*	str = NULL;
	char*	data = NULL;
	char*	value = NULL;
	tStat	info;

	lstat(path, &info);

	if (S_ISLNK(info.st_mode) == true)
		data = getDup("l");
	else if (S_ISDIR(info.st_mode) == true)
		data = getDup("d");

	if (S_ISLNK(info.st_mode) == false && S_ISDIR(info.st_mode) == false)
		data = getDup("-");

	value = getRight(1, info.st_mode), str = data;
	data = getJoin(data, value, "\0");
	free(value), free(str);

	value = getRight(2, info.st_mode), str = data;
	data = getJoin(data, value, "\0");
	free(value), free(str);

	value = getRight(3, info.st_mode), str = data;
	data = getJoin(data, value, "\0");
	free(value), free(str);

	value = getNumber(info.st_nlink), str = data;
	data = getJoin(data, " ", value);
	free(value), free(str);

	value = getpwuid(info.st_uid)->pw_name, str = data;
	data = getJoin(data, " ", value);
	free(str);

	value = getgrgid(info.st_gid)->gr_name, str = data;
	data = getJoin(data, " ", value);
	free(str);

	return (data);
}

void	printListing(char* path)
{
	char*	data = NULL;
	char*	date = NULL;
	char*	size = NULL;

	data = getData(path);
	writeStr(data, 1);
	writeStr(" ", 1);
	free(data);

	date = getDate(path);
	writeStr(date, 1);
	writeStr(" ", 1);

	size = getSize(path);
	writeStr(size, 1);
	writeStr(" ", 1);
	free(size);
}
