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
    char* string = (char*)malloc(sizeof (char) * STRING_SIZE);
    if (!string)
    {
        printf(MALLOC_ERR_MSG);
        return NULL;
    }

    char chunk[CHUNK_SIZE];
    size_t tmp_size = STRING_SIZE;
    unsigned int tmp_number_of_elements = 0;

    while (fgets(chunk, CHUNK_SIZE, TMP_IN_FILE))
    {
        if (tmp_number_of_elements + strlen(chunk) > tmp_size)
        {
            char* test_realloc = (char*)realloc(string, sizeof(char)*tmp_size*EXPANSION_KOEF);
            if (!test_realloc)
            {
                printf(REALLOC_ERR_MSG);
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
        printf(REALLOC_ERR_MSG);
        free(string);
        return NULL;
    }

    string = test_realloc;

    return string;
}

char** read_text(size_t *size)
{
    char** result = (char**)malloc(sizeof(char*)*RESULT_SIZE);
    if (!result)
    {
        printf(MALLOC_ERR_MSG);
        return NULL;
    }

    size_t i = 0;
    size_t tmp_size = RESULT_SIZE;
    int end_line_flag = 0;

    while(1)
    {
        char* string = read_string();
        if (!string)
        {
            free(result);
            return NULL;
        }

        if (isEndLine(string))
        {
            int string_length = strlen(string);
            string[string_length - 3] = '\0';
            string_length -= 2;

            char *test_realloc = (char *) realloc(string, string_length + BYTE_FOR_NUL);
            if (!test_realloc)
            {
                printf(REALLOC_ERR_MSG);
                free(string);
                free(result);
                return NULL;
            }

            string = test_realloc;
            end_line_flag = 1;
        }

        result[i] = string;
        i++;

        if(i == tmp_size)
        {
            char** test_realloc = (char**)realloc(result, sizeof(char*)*tmp_size*EXPANSION_KOEF);
            if (!test_realloc)
            {
                free(result);
                printf(REALLOC_ERR_MSG);
                return NULL;
            }
            tmp_size *= EXPANSION_KOEF;
            result = test_realloc;
        }

        if (end_line_flag)
        {
            break;
        }
    }

    char** test_realloc = (char**)realloc(result, sizeof(char*)*i);
    if (!test_realloc)
    {
        free(result);
        printf(REALLOC_ERR_MSG);
        return NULL;
    }
    result = test_realloc;

    *size = i;
    return result;
}
