#include "../include/count.h"

#define NULL_ARRAY_ERR_MSG "Wrong array (= NULL)!\n"
#define INVALID_SIZE_ERR_MSG "Size should be positive number\n"
int count_novoices_comments(Comment* array, int size)
{
    if (!array) {
        fprintf(TMP_OUT_FILE, NULL_ARRAY_ERR_MSG);
        return NULL_ARRAY_ERROR;
    }
    if (size <= 0) {
        fprintf(TMP_OUT_FILE, INVALID_SIZE_ERR_MSG);
        return INVALID_SIZE_ERROR;
    }

    int counter = 0;
    for(int i = 0; i < size; i++){
        if(array[i].voices == 0)
            counter++;
    }
    return counter;
}
