#include "../include/count.h"

int count_novoices_comments(Comment* array, int size)
{
    if (!array)
        return NULL_ARRAY_ERROR;

    if (size <= 0)
        return INVALID_SIZE_ERROR;

    int counter = 0;
    for(int i = 0; i < size; i++)
        if(array[i].voices == 0)
            counter++;
        
    return counter;
}
