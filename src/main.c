#include <stdio.h>
#include <stdlib.h>

#include "../include/DVB_file.h"
#include "../include/DVB_parse.h"

int main(int argc, char **argv)
{
	int desfile    = -1;
	int sizefile   = -1;
	int read_bytes = -1;
	char* buffer   = NULL;
	
	//check arguments
    if (argc != 2)
	{
        printf("Name file is error or null\n");
		return -1;
    }
   	
	//get size file
	sizefile = get_size(argv[1]);
    if (sizefile == -1)
    {
        printf("Error size file\n");
		return -1;
    }
	
	//open file
    desfile = file_open(argv[1]);
    if ( desfile != -1)
    {
		printf("Error open file\n");
		return -1;
	}
	
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
	free(buffer);
	return 0;
}