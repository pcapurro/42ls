#include "../include/header.h"

int		getStrLen(const char* str)
{
	int len = 0;
	for (int i = 0; str != NULL && str[i] != '\0'; i++)
		len++;

	return (len);
}

int		getArrLen(char** str)
{
	int len = 0;
	for (int i = 0; str != NULL && str[i] != NULL; i++)
		len++;

	return (len);
}

char*	getDup(const char* str)
{
	int		len = 0;
	char*	string;

	for (int i = 0; str[i] != '\0'; i++)
		len++;
	string = malloc(sizeof(char) * (len + 1));
	if (!string || string == NULL)
		return (NULL);

	for (int i = 0; str[i] != '\0'; i++)
		string[i] = str[i];

	return (string);
}

void	writeStr(const char* str, int fd)
{
	for (int i = 0; str[i] != '\0'; i++)
		write(fd, &str[i], 1);
}
