#ifndef PT_2_THREADS_LIBRARY_H
#define PT_2_THREADS_LIBRARY_H

#include "header.h"

#define PTHREAD_CREATE_ERROR -1
#define SYSCONF_ERROR -3
#define NULL_ARRAY_ERROR -4
#define INVALID_SIZE_ERROR -5

int count_novoices_comments(Comment* array, int size);

#endif //PT_2_THREADS_LIBRARY_H
