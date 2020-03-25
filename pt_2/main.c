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
    __asm__ __volatile__("rdtsc"
    : "=A"(t));
    return t;
}

#define USAGE_MESG "usage: <filename> or <path> <filename>"
#define WRONG_LAUNCH_ERROR -1
#define READ_FILE_ERROR -2
int main(int argc, char** argv)
{
    char* filename = NULL;
    if (argc == 1)
        filename = "stress_test_files/1000.txt";
    else if (argc == 2)
        filename = argv[1];
    else if (argc == 3)
        filename = strcat(argv[1], argv[2]);
    else {
        fprintf(TMP_OUT_FILE, USAGE_MESG);
        return WRONG_LAUNCH_ERROR;
    }

    int size = 0;
    Comment* comments = NULL;
    int error_code = read_array_from_file(filename, &comments, &size);
    const char* error_message = get_error_message(error_code);
    if (error_message) {
        fprintf(TMP_OUT_FILE, error_message);
        return READ_FILE_ERROR;
    }

    if (comments) {
        long long start_time = tick();
        int result = count_novoices_comments(comments, size);
        long long end_time = tick();
        fprintf(TMP_OUT_FILE, "result = %d, time: %llu\n", result, end_time - start_time);
        free(comments);
    }

    return 0;
}
