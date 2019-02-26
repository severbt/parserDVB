#include "../include/utils.h"

void swap_byte(char* v1, char* v2)
{
    char tmp = (*v1);
    (*v1) = (*v2);
    (*v2) = tmp;
}

/*void swap_arr(void* a1, void* a2)
{


}*/
