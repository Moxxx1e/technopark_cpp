#ifndef PT_2_ERROR_HANDLER_H
#define PT_2_ERROR_HANDLER_H

#include "header.h"

// read errors
#define SUCCESS 0

#define FILE_OPEN_ERROR -1
#define FILE_OPEN_ERR_MSG "Unable to open file!"

#define EMPTY_FILE_ERROR -2
#define EMPTY_FILE_ERR_MSG "File is empty!"

#define FSCANF_NUMBER_OF_COMMENTS_ERROR -3
#define FSCANF_NUMBER_OF_COMMENTS_ERR_MSG "Wrong number of comments!"

#define NOT_POSITIVE_NUMBER_OF_COMMENTS_ERROR -4
#define NOT_POSITIVE_NUMBER_OF_COMMENTS_ERR_MSG "Number of comments should be positive number!"

#define FSCANF_ID_ERROR -5
#define FSCANF_ID_ERR_MSG "Error while reading ID!"

#define INVALID_MARK_ERROR -6
#define INVALID_MARK_ERR_MSG "Mark must be 0 or number between 1.0 and 5.0!"

#define FSCANF_MARK_ERROR -7
#define FSCANF_MARK_ERR_MSG "Error while reading mark!"

#define FSCANF_VOICES_ERROR -8
#define FSCANF_VOICES_ERR_MSG "Error while reading voices!"

#define INVALID_VOICES_ERROR -9
#define INVALID_VOICES_ERR_MSG "Error! Voices should be not negative number!"

#define INCORRECT_NUMBER_OF_COMMENTS_ERROR -10
#define INCORRECT_NUMBER_OF_COMMENTS_ERR_MSG "Number of comments is more than actual number!"

#define ALLOC_ERROR -11
#define ALLOC_ERR_MSG "Malloc error!"

// count errors
#define NULL_ARRAY_ERROR -12
#define NULL_ARRAY_ERR_MSG "Wrong array (= NULL)!\n"

#define INVALID_SIZE_ERROR -13
#define INVALID_SIZE_ERR_MSG "Size should be positive number\n"

#define ALLOC_FOR_THREAD_ERROR -14
#define ALLOC_FOR_THREAD_ERR_MSG "Unable to alloc memory for threads!"

#define PTHREAD_CREATE_ERROR -15
#define PTHREAD_CREATE_ERR_MSG "Unable to create thread!\n"

const char* get_error_message(int error_code);

#endif //PT_2_ERROR_HANDLER_H
