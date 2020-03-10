#include "filter.h"

int symbolInBufer(char symbol, const char* const bufer, size_t bufer_size)
{
    for (size_t i = 0; i < bufer_size; ++i)
    {
        if (bufer[i] == symbol)
        {
            return 1;
        }
    }
    return 0;
}

#define DIFF_SYMBOLS_NUM 3

int isStringGood(const char* const string)
{
    char symbols_bufer[DIFF_SYMBOLS_NUM] = {0};
    int i = 0;
    int bufer_elements_counter = 0;
    
    while (string[i] != '\0')
    {
        if (string[i] == '\n')
        {
            break;
        }

        if (symbolInBufer(string[i], symbols_bufer, DIFF_SYMBOLS_NUM))
        {
            i++;
            continue;
        }

        symbols_bufer[bufer_elements_counter] = string[i];
        bufer_elements_counter++;
        if (bufer_elements_counter == DIFF_SYMBOLS_NUM)
            return 1;
        i++;
    }
    return 0;
}

int filter(const char** const source, int number_of_strings, Node** head_result)
{
    for (int i = 0; i < number_of_strings; ++i)
    {
        if (isStringGood(source[i]))
        {
            Node* new_element = create_node(source[i]);
            *head_result = append_to_list(*head_result, new_element);
        }
    }

    return list_size(*head_result);
}
