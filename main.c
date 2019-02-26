#include <stdio.h>

#include "include/parse_stream_packet.h"

int main()
{
    //test1
    {
    unsigned char str[] = { 0x47, 5, 8, 9, '10', '\0' };
    const unsigned char* tmp;
    tmp = find_start(str);
    printf("stream =%s\n", tmp);
    }

    {
    //test2
    char* p = malloc(10);
    unsigned char str[] = { 0x47, 0xE0, 0x10, 0xFF };
    parse_packet(str, 0x0010,p);
    free(p);


    //unsigned char str[] = { 0x47, 5, 8, 9, '10', '\0' };


    //unsigned char str[] = { 0x47, 5, 8, 9, '10', '\0' };
    }




    return 0;
}
