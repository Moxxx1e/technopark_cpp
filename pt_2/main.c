#include <stdio.h>
#include "stdlib.h"
#include "string.h"

#ifndef SHARED
#include "pt_2_shared/include/read.h"
#include "pt_2_shared/include/count.h"
#else
#include "pt_2_static/include/read.h"
#include "pt_2_static/include/count.h"
#endif

unsigned long long tick()
{
    unsigned long long t;
    __asm__ __volatile__ ("rdtsc" : "=A" (t));
    return t;
}

int main(int argc, char** argv)
{
    char* filename = NULL;
    if (argc != 2){
        filename = "stress_test_files/1000.txt";
    }
    else{
        filename = argv[1];
    }

    int size = 0;
    Comment* comments = NULL;
    read_array_from_file(filename, &comments, &size);

    if (comments)
    {
        long long start_time = tick();
        int result = count_novoices_comments(comments, size);
        long long end_time = tick();
        fprintf(TMP_OUT_FILE, "result = %d, time: %llu\n", result, end_time - start_time);
        free(comments);
    }

    return 0;
}
