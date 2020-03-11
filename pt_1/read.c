#include "header.h"
#include "read.h"

#define CHUNK_SIZE 64
#define EXPANSION_KOEF 2
#define BYTE_FOR_NUL 1
#define RESULT_SIZE 20
#define STRING_SIZE 1024

int isEndLine(char* string)
{
    if (strlen(string) >= 3)
    {
        if (string[strlen(string) - 3] == '^' && string[strlen(string) - 2] == 'X' )
        {
            return 1;
        }
    }
    else if (strlen(string) == 2)
    {
        if (string[0] == '^' && string[1] == 'X')
        {
            return 1;
        }
    }
    return 0;
}

char* read_string()
{
    char* string = (char*)malloc(sizeof(char) * STRING_SIZE);
    if (!string)
    {
        fprintf(TMP_OUT_FILE, MALLOC_ERR_MSG);
        return NULL;
    }

    char chunk[CHUNK_SIZE];
    size_t tmp_size = STRING_SIZE;
    unsigned int tmp_number_of_elements = 0;

    while (fgets(chunk, CHUNK_SIZE, TMP_IN_FILE))
    {
        if (tmp_number_of_elements + strlen(chunk) > tmp_size)
        {
            char* test_realloc = (char*)realloc(string, sizeof(char) * tmp_size * EXPANSION_KOEF);
            if (!test_realloc)
            {
                fprintf(TMP_OUT_FILE, REALLOC_ERR_MSG);
                free(test_realloc);
                free(string);
                return NULL;
            }
            string = test_realloc;
            tmp_size *= EXPANSION_KOEF;
        }
        memcpy(string + tmp_number_of_elements, chunk, strlen(chunk) + BYTE_FOR_NUL);
        tmp_number_of_elements += strlen(chunk);
        if (chunk[strlen(chunk) - 1] == '\n')
            break;
    }

    char* test_realloc = (char*)realloc(string, strlen(string) + BYTE_FOR_NUL);
    if (!test_realloc)
    {
        fprintf(TMP_OUT_FILE, REALLOC_ERR_MSG);
        free(string);
        return NULL;
    }

    string = test_realloc;

    return string;
}

char** read_text(unsigned int *number_of_elements)
{
    char** vector_of_strings = (char**)malloc(sizeof(char*) * RESULT_SIZE);
    if (!vector_of_strings)
    {
        fprintf(TMP_OUT_FILE, MALLOC_ERR_MSG);
        return NULL;
    }

    unsigned int i = 0;
    size_t tmp_size = RESULT_SIZE;
    int end_line_flag = 0;

    while(1)
    {
        char* string = read_string();
        if (!string)
        {
            free(vector_of_strings);
            return NULL;
        }

        if (isEndLine(string))
        {
            unsigned long string_length = strlen(string);
            string[string_length - 3] = '\0';
            string_length -= 2;

            char *test_realloc = (char *)realloc(string, sizeof(char) * (string_length + BYTE_FOR_NUL));
            if (!test_realloc)
            {
                fprintf(TMP_OUT_FILE, REALLOC_ERR_MSG);
                free(string);
                free(vector_of_strings);
                return NULL;
            }

            string = test_realloc;
            end_line_flag = 1;
        }

        vector_of_strings[i] = string;
        i++;

        if(i == tmp_size)
        {
            char** test_realloc = (char**)realloc(vector_of_strings, sizeof(char*) * tmp_size * EXPANSION_KOEF);
            if (!test_realloc)
            {
                free(vector_of_strings);
                fprintf(TMP_OUT_FILE, REALLOC_ERR_MSG);
                return NULL;
            }
            tmp_size *= EXPANSION_KOEF;
            vector_of_strings = test_realloc;
        }

        if (end_line_flag)
        {
            break;
        }
    }

    char** test_realloc = (char**)realloc(vector_of_strings, sizeof(char*) * i);
    if (!test_realloc)
    {
        free(vector_of_strings);
        fprintf(TMP_OUT_FILE, REALLOC_ERR_MSG);
        return NULL;
    }
    vector_of_strings = test_realloc;

    *number_of_elements = i;
    return vector_of_strings;
}
