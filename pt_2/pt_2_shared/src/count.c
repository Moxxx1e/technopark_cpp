#include "../include/count.h"

typedef unsigned int __attribute((aligned(64))) al64uint_t;
typedef long __attribute((aligned(64))) al64long_t;

typedef struct Thread_data {
    Comment_shared* array;
    unsigned int size;
    int counter;
} Thread_data;

void* count(void* arg)
{
    Thread_data* data = (Thread_data*)arg;

    for (int i = 0; i < data->size; i++)
        if (data->array[i].voices == 0)
            data->counter++;

    pthread_exit(0);
}

Thread_data* create_thread_data_array(Comment_shared* array, unsigned int size,
                                      long number_of_threads, unsigned int section_size)
{
    long l1dcls = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    if (l1dcls == -1)
        l1dcls = sizeof(void*);

    Thread_data* thread_data_array = NULL;
    int err_flag = posix_memalign((void**)&thread_data_array,
                                  l1dcls, number_of_threads * sizeof(Thread_data));
    if (err_flag)
        return NULL;

    int i = 0;
    for (i = 0; i < number_of_threads; i++) {
        thread_data_array[i].array = array;
        thread_data_array[i].counter = 0;
        thread_data_array[i].size = section_size;
        array += section_size;
    }
    thread_data_array[number_of_threads - 1].size += size - section_size * number_of_threads;

    return thread_data_array;
}

int count_novoices_comments(Comment_shared* array, int size)
{
    if (!array)
        return NULL_ARRAY_ERROR;
    if (size <= 0)
        return INVALID_SIZE_ERROR;

    al64long_t number_of_threads = sysconf(_SC_NPROCESSORS_ONLN);

    pthread_t pthread_t_array[number_of_threads];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    al64uint_t section_size = size / number_of_threads;

    Thread_data* thread_data_array = create_thread_data_array(array, size, number_of_threads, section_size);
    if (thread_data_array == NULL)
        return ALLOC_FOR_THREAD_ERROR;

    for (int i = 0; i < number_of_threads; i++) {
        int error_code = pthread_create(&(pthread_t_array[i]), &attr,
                                        count, &thread_data_array[i]);
        if (error_code)
            return PTHREAD_CREATE_ERROR;

        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(i, &cpuset);
        int rc = pthread_setaffinity_np(pthread_t_array[i], sizeof(cpu_set_t), &cpuset);
        if (rc != 0)
            fprintf(TMP_OUT_FILE, "Error calling pthread_setaffinity_np: %d\n", rc);
    }

    int counter = 0;
    for (int i = 0; i < number_of_threads; i++) {
        pthread_join(pthread_t_array[i], 0);
        counter += thread_data_array[i].counter;
    }

    free(thread_data_array);
    return counter;
}
