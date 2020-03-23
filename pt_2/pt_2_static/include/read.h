#ifndef PT_2_READ_H
#define PT_2_READ_H

#include "header.h"

#define SUCCESS 0
#define FILE_OPEN_ERROR -1
#define EMPTY_FILE_ERROR -2
// unable to read number of comments (not integer)
#define FSCANF_NUMBER_OF_COMMENTS_ERROR -3
// number is negative or zero
#define NOT_POSITIVE_NUMBER_OF_COMMENTS_ERROR -4
#define FSCANF_ID_ERROR -5
#define INVALID_MARK_ERROR -6
#define FSCANF_MARK_ERROR -7
#define FSCANF_VOICES_ERROR -8
#define INVALID_VOICES_ERROR -9
// There are more comments in file than number said
#define INCORRECT_NUMBER_OF_COMMENTS_ERROR -10
#define MALLOC_ERROR -11

int read_array_from_file(const char* in_file_name, Comment** array, int* size);

#endif
