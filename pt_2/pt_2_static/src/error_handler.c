#include "../include/error_handler.h"

const char* get_error_message(int error_code)
{
    switch (error_code){
        case FILE_OPEN_ERROR:
            return FILE_OPEN_ERR_MSG;

        case EMPTY_FILE_ERROR:
            return EMPTY_FILE_ERR_MSG;

        case FSCANF_NUMBER_OF_COMMENTS_ERROR:
            return FSCANF_NUMBER_OF_COMMENTS_ERR_MSG;

        case NOT_POSITIVE_NUMBER_OF_COMMENTS_ERROR:
            return NOT_POSITIVE_NUMBER_OF_COMMENTS_ERR_MSG;

        case FSCANF_ID_ERROR:
            return FSCANF_ID_ERR_MSG;

        case INVALID_MARK_ERROR:
            return INVALID_MARK_ERR_MSG;

        case FSCANF_MARK_ERROR:
            return FSCANF_MARK_ERR_MSG;

        case FSCANF_VOICES_ERROR:
            return FSCANF_VOICES_ERR_MSG;

        case INVALID_VOICES_ERROR:
            return INVALID_VOICES_ERR_MSG;

        case INCORRECT_NUMBER_OF_COMMENTS_ERROR:
            return INCORRECT_NUMBER_OF_COMMENTS_ERR_MSG;

        case ALLOC_ERROR:
            return ALLOC_ERR_MSG;

        case NULL_ARRAY_ERROR:
            return NULL_ARRAY_ERR_MSG;

        case INVALID_SIZE_ERROR:
            return INVALID_SIZE_ERR_MSG;
    }
    return NULL;
}