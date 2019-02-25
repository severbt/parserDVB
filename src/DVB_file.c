#include <sys/stat.h>
//#include <fcntl.h> // ???
#include <unistd.h>

#include "../include/DVB_file.h"

int open_file( const char* name)
{
	int des_file = -1;
	des_file = open(name, O_BINARY | O_RDONLY);
	return (des_file);
}

int get_size(const char* name)
{
	struct stat sb = {};
    if (stat(name &sb) == -1)
    {
		return (-1);
	}	
	return ((int)sb.st_size);
}

int read_file( int fd, char *buf, size_t count)
{
	int bytes = -1;
	bytes = (int)read(fd, buf, count);
	return (bytes);
}

int close_file( const int desc)
{
	int result = -1;
	result = close(desc);
	return (result);
}