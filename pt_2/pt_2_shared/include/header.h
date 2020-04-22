#ifndef PT_2_THREADS_HEADER_H
#define PT_2_THREADS_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#define __USE_GNU
#include <sched.h>
#include <unistd.h>
#include <pthread.h>

#define TMP_OUT_FILE stdout

typedef struct Comment{
    unsigned int voices;
    int id;
    double mark;
} Comment_shared;

#endif
