#include <stdio.h>
#include "stdlib.h"

#ifndef SHARED
#include "pt_2_shared/include/read.h"
#include "pt_2_shared/include/count.h"
#else
#include "pt_2_static/include/read.h"
#include "pt_2_static/include/count.h"
#endif

#include "string.h"

unsigned long long tick()
{
    unsigned long long t;
    __asm__ __volatile__ ("rdtsc" : "=A" (t));
    return t;
}

double get_rand_mark()
{
    double value = rand() % 41 + 10;
    value /= 10;
    return value;
}

#define MAX_NUMBER_OF_VOICES 100
#define DESIRED_PERCENTAGE_OF_NOVOICE_COMMENTS 40
void generate_correct_file(const char* filename, int size)
{
    int id;
    double mark;
    unsigned int voices;

    FILE* f = fopen(filename, "w");

    fprintf(f, "%d\n ", size);
    for (int i = 0; i < size; i++){
        id = i;
        int flag = rand() % 100 + 1;

        if (flag > DESIRED_PERCENTAGE_OF_NOVOICE_COMMENTS){
            mark = get_rand_mark();
            voices = rand() % MAX_NUMBER_OF_VOICES;
        }
        else{
            mark = 0;
            voices = 0;
        }

        fprintf(f, "%d ", id);
        fprintf(f, "%lf ", mark);
        fprintf(f, "%d\n", voices);
    }
    fclose(f);
}

int main(int argc, char** argv)
{
    char* filename;
    if (argc != 2){
        filename = "../1000.txt";
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
