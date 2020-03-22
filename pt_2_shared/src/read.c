#include "../include/read.h"

#define unlikely(expr) __builtin_expect(!!(expr), 0)

#define EMPTY_FILE_ERR_MSG "File is empty!\n"
#define FSCANF_NUMBER_OF_COMMENTS_ERR_MSG "Wrong number of comments!\n"
#define INVALID_NUMBER_OF_COMMENTS_ERR_MSG "Number of comments should be positive number!\n"
int read_number_of_comments(FILE* in_file, int* number_of_comments)
{
    int error_code = fscanf(in_file, "%d", number_of_comments);

    if (error_code == EOF){
        fprintf(TMP_OUT_FILE, EMPTY_FILE_ERR_MSG);
        return EMPTY_FILE_ERROR;
    }

    if (error_code != 1){
        fprintf(TMP_OUT_FILE, FSCANF_NUMBER_OF_COMMENTS_ERR_MSG);
        return FSCANF_NUMBER_OF_COMMENTS_ERROR;
    }

    if (*number_of_comments <= 0){
        fprintf(TMP_OUT_FILE, INVALID_NUMBER_OF_COMMENTS_ERR_MSG);
        return NOT_POSITIVE_NUMBER_OF_COMMENTS_ERROR;
    }

    return SUCCESS;
}

Comment* alloc_for_array(int number_of_comments, int* error_code)
{
    long l1dcls = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    if (l1dcls == -1)
        l1dcls = sizeof(void*);

    Comment* array = NULL;
    *error_code = posix_memalign((void**)&array, l1dcls, sizeof(Comment) * number_of_comments);
    if (*error_code){
        *error_code = POSIX_MEMALIGN_ERROR;
        fprintf(TMP_OUT_FILE, POSIX_MEMALIGN_ERR_MSG);
        return NULL;
    }
    return array;
}

#define FSCANF_ID_ERR_MSG "Error while reading ID!"
#define INCORRECT_NUMBER_OF_COMMENTS_ERR_MSG "Number of comments is more than actual number!"
int read_id(FILE* in_file, int* id)
{
    int error_code = fscanf(in_file, "%d", id);

    if (error_code == EOF){
        fprintf(TMP_OUT_FILE, INCORRECT_NUMBER_OF_COMMENTS_ERR_MSG);
        return INCORRECT_NUMBER_OF_COMMENTS_ERROR;
    }

    if (error_code != 1){
        fprintf(TMP_OUT_FILE, FSCANF_ID_ERR_MSG);
        return FSCANF_ID_ERROR;
    }
    return SUCCESS;
}

#define LEFT_MARK_BOUNDARY 10
#define RIGHT_MARK_BOUNDARY 50
int isMarkValid(double mark)
{
    return mark == 0 || (mark*10 >= LEFT_MARK_BOUNDARY && mark*10 <= RIGHT_MARK_BOUNDARY);
}

#define FSCANF_MARK_ERR_MSG "Error while reading mark!\n"
#define INVALID_MARK_ERR_MSG "Error! Mark must be 0 or number between 1.0 and 5.0!"
int read_mark(FILE* in_file, double* mark)
{
    int error_code = fscanf(in_file, "%lf", mark);

    if (error_code != 1){
        fprintf(TMP_OUT_FILE, FSCANF_MARK_ERR_MSG);
        return FSCANF_MARK_ERROR;
    }

    if (!isMarkValid(*mark)){
        fprintf(TMP_OUT_FILE, INVALID_MARK_ERR_MSG);
        return INVALID_MARK_ERROR;
    }

    return SUCCESS;
}

#define INVALID_VOICES_ERR_MSG "Error! Voices should be not negative number!"
#define FSCANF_VOICES_ERR_MSG "Error while reading voices!"
int read_voices(FILE* in_file, unsigned int* voices)
{
    int int_voices = 0;
    int error_code = fscanf(in_file, "%d", &int_voices);
    if (error_code != 1){
        fprintf(TMP_OUT_FILE, FSCANF_VOICES_ERR_MSG);
        return FSCANF_VOICES_ERROR;
    }

    if (int_voices < 0){
        fprintf(TMP_OUT_FILE, INVALID_VOICES_ERR_MSG);
        return INVALID_VOICES_ERROR;
    }

    *voices = (unsigned int) int_voices;

    return SUCCESS;
}

#define FILE_OPEN_ERR_MSG "Unable to open file!\n"
int read_array_from_file(const char* in_file_name, Comment* array)
{
    FILE* in_file = fopen(in_file_name, "r");
    if (!in_file){
        fprintf(TMP_OUT_FILE, FILE_OPEN_ERR_MSG);
        return FILE_OPEN_ERROR;
    }

    int number_of_comments = 0;
    int error_number_of_comments = read_number_of_comments(in_file, &number_of_comments);
    if (error_number_of_comments < 0){
        fclose(in_file);
        return error_number_of_comments;
    }

    int error_alloc = SUCCESS;
    array = alloc_for_array(number_of_comments, &error_alloc);
    if (!array){
        fclose(in_file);
        return error_alloc;
    }

    int id = 0;
    double mark = 0;
    unsigned int voices = 0;
    int error_id, error_mark, error_voices = 0;
    for(int i = 0; i < number_of_comments; i++){
        error_id = read_id(in_file, &id);
        error_mark = read_mark(in_file, &mark);
        error_voices = read_voices(in_file, &voices);

        if (unlikely(error_id < 0 || error_mark < 0 || error_voices < 0)){
            free(array);
            fclose(in_file);
            fprintf(TMP_OUT_FILE, " In %d string.\n", i);
            if (error_id < 0)
                return error_id;
            if (error_mark < 0)
                return error_mark;
            if (error_voices < 0)
                return error_voices;
        }

        array[i].voices = voices;
        array[i].id = id;
        array[i].mark = mark;
    }

    fclose(in_file);
    return SUCCESS;
}