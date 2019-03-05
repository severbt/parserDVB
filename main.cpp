#include "include/DVB_reader.h"

#include <iostream>

using namespace DVB;

int main(int argc, char **argv)
{
	int desfile    = -1;
	int sizefile   = -1;
	int read_bytes = -1;
	char* buffer   = NULL;

	DVB_reader reader;

	//check arguments
    //if (argc != 2)
	//{
    //    printf("Name file is error or null\n");
	//	return -1;
    //}

    char name_file[] = "tablas_DTH.ts";
    if ( reader.Open(name_file))
    //if ( reader.Open(argv[1]))
    {
		printf("Error open file\n");
		return -1;
	}

	reader.RunParser();

	return std::cin.get(), 0;
}
