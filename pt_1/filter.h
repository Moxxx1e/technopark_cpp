#ifndef FILTER_H
#define FILTER_H

#include "header.h"
#include "list.h"

int filter(char** source, unsigned int number_of_strings, Node** head_result);

int symbolInBufer(char symbol, const char* const bufer, size_t bufer_size);

int isStringGood(const char* string);

#endif // FILTER_H
