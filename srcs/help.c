#include "../include/header.h"

void	printHelp(void)
{
	writeStr("Usage: ./42ls [paths] [options]\n", 1);
	writeStr("Supported options: -l, -R, -a, -r and -t.\n", 1);
}

bool	isHelp(const char* str)
{
	if (getStrLen(str) != 6)
		return (false);

	if (str[0] == '-' && str[1] == '-' && str[2] == 'h' \
		&& str[3] == 'e' && str[4] == 'l' && str[5] == 'p')
		return (true);
	
	return (false);
}
