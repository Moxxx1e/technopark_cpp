#ifndef PT_2_THREADS_READ_H
#define PT_2_THREADS_READ_H

#include "header.h"
#include "error_handler.h"

int read_array_from_file_sh(const char* in_file_name, Comment_shared** array, int* size);

#endif
