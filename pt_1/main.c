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
    unsigned int number_of_elements = 0;
    char** vector = read_text(&number_of_elements);
    if (!vector)
    {
        return -1;
    }

    Node* result = NULL;
    output_result_message();
    int res = filter(vector, number_of_elements, &result);
    if (res == 0)
        fprintf(TMP_OUT_FILE, "Filter is empty!");
    else
        print_list(result);

    free_list(result);
    for (int i = 0; i < number_of_elements; ++i)
    {
        free(vector[i]);
    }
    free(vector);
    return 0;
}
