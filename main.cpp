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

	/*
	//allocate memory
	buffer = (char*)calloc(desfile, 1);
	if (buffer == NULL)
	{
		printf("Error calloc\n");
		close(desfile);
		return -1;
	}

	//read file
	read_bytes = read_file(desfile, buffer, sizefile);
	if (read_bytes == -1)
	{
		printf("Error read file\n");
		close(desfile);
		free(buffer);
		return -1;
	}


	close(desfile);
	free(buffer);*/
	return std::cin.get(), 0;
}
