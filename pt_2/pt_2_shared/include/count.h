#ifndef PT_2_THREADS_LIBRARY_H
#define PT_2_THREADS_LIBRARY_H

#include "header.h"
#include "error_handler.h"

#define SYSCONF_ERROR -3
#define PTHREAD_CREATE_ERROR -4
#define ALLOC_FOR_THREAD_ERROR -5

int count_novoices_comments(Comment* array, int size);

#endif
