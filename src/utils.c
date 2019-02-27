#include <stdlib.h>

#include "../include/utils.h"

void swap_byte(unsigned char* v1, unsigned char* v2)
{
    char tmp = (*v1);
    (*v1) = (*v2);
    (*v2) = tmp;
}

/*void swap_arr(void* a1, void* a2)
{


}*/
unsigned char* allocate_uc( const unsigned int s)
{
    unsigned char* p = NULL;
    p = (unsigned char*)calloc(s, sizeof(unsigned char));
    return p;
}

unsigned char* reallocate_uc( const unsigned int s, unsigned char* p)
{
    clear_uc(p);

    p = (unsigned char*)calloc(s, sizeof(unsigned char));
    return p;
}

void clear_uc( unsigned char* p)
{
    if ( p != NULL)
    {
        free(p);
    }
}
