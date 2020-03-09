#include <header.h>
#include "list.h"
#include "read.h"
#include "filter.h"

void output_hello_message()
{
    fprintf(TMP_OUT_FILE, "Input text (type ^X to finish typing): \n");
}

void output_result_message()
{
    fprintf(TMP_OUT_FILE,"\nResult: \n");
}

#define RESULT_SIZE 20

int main(void)
{
    output_hello_message();
    int size = 0;
    const char** vector = read_text(&size);
    if (!vector)
    {
        return -1;
    }

    Node* result = NULL;
    output_result_message();
    int res = filter(vector, size, &result);
    if (res == 0)
        fprintf(TMP_OUT_FILE, "Filter is empty!");
    else
        print_list(result);

    free_list(result);
    for (int i = 0; i < size; ++i)
    {
        free(vector[i]);
    }
    free(vector);
    return 0;
}
