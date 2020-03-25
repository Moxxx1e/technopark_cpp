#include "../include/read.h"

#define unlikely(expr) __builtin_expect(!!(expr), 0)

int read_number_of_comments(FILE* in_file, int* number_of_comments)
{
    int error_code = fscanf(in_file, "%d", number_of_comments);

    if (error_code == EOF)
        return EMPTY_FILE_ERROR;

    if (error_code != 1)
        return FSCANF_NUMBER_OF_COMMENTS_ERROR;

    if (*number_of_comments <= 0)
        return NOT_POSITIVE_NUMBER_OF_COMMENTS_ERROR;

    return SUCCESS;
}

Comment* alloc_for_array(int number_of_comments, int* error_code)
{
    long l1dcls = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    if (l1dcls == -1)
        l1dcls = sizeof(void*);

    Comment* array = NULL;
    *error_code = posix_memalign((void**)&array, l1dcls, sizeof(Comment) * number_of_comments);
    if (*error_code) {
        *error_code = ALLOC_ERROR;
        return NULL;
    }
    return array;
}

int read_id(FILE* in_file, int* id)
{
    int error_code = fscanf(in_file, "%d", id);

    if (error_code == EOF)
        return INCORRECT_NUMBER_OF_COMMENTS_ERROR;

    if (error_code != 1)
        return FSCANF_ID_ERROR;

    return SUCCESS;
}

#define LEFT_MARK_BOUNDARY 10
#define RIGHT_MARK_BOUNDARY 50
int isMarkValid(double mark)
{
    return mark == 0 || (mark * 10 >= LEFT_MARK_BOUNDARY && mark * 10 <= RIGHT_MARK_BOUNDARY);
}

int read_mark(FILE* in_file, double* mark)
{
    int error_code = fscanf(in_file, "%lf", mark);

    if (error_code != 1)
        return FSCANF_MARK_ERROR;

    if (!isMarkValid(*mark))
        return INVALID_MARK_ERROR;

    return SUCCESS;
}

int read_voices(FILE* in_file, unsigned int* voices)
{
    int int_voices = 0;
    int error_code = fscanf(in_file, "%d", &int_voices);
    if (error_code != 1)
        return FSCANF_VOICES_ERROR;

    if (int_voices < 0)
        return INVALID_VOICES_ERROR;

    *voices = (unsigned int)int_voices;

    return SUCCESS;
}

int read_array_from_file(const char* in_file_name, Comment** array, int* size)
{
    FILE* in_file = fopen(in_file_name, "r");
    if (!in_file)
        return FILE_OPEN_ERROR;

    int number_of_comments = 0;
    int error_number_of_comments = read_number_of_comments(in_file, &number_of_comments);
    if (error_number_of_comments < 0) {
        fclose(in_file);
        return error_number_of_comments;
    }

    int error_alloc = SUCCESS;
    *array = alloc_for_array(number_of_comments, &error_alloc);
    if (!(*array)) {
        fclose(in_file);
        return error_alloc;
    }

    int id = 0;
    double mark = 0;
    unsigned int voices = 0;
    int error_id, error_mark, error_voices = 0;
    for (int i = 0; i < number_of_comments; i++) {
        error_id = read_id(in_file, &id);
        error_mark = read_mark(in_file, &mark);
        error_voices = read_voices(in_file, &voices);

        if (unlikely(error_id < 0 || error_mark < 0 || error_voices < 0)) {
            free(*array);
            fclose(in_file);
            fprintf(TMP_OUT_FILE, " In %d string.\n", i);
            if (error_id < 0)
                return error_id;
            if (error_mark < 0)
                return error_mark;
            if (error_voices < 0)
                return error_voices;
        }

        (*array)[i].voices = voices;
        (*array)[i].id = id;
        (*array)[i].mark = mark;
    }

    *size = number_of_comments;
    fclose(in_file);
    return SUCCESS;
}
