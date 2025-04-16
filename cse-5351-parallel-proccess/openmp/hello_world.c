#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void print_thread_id(int val);

int main()
{
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        print_thread_id(id);
    }

    double A[1000];
    omp_set_num_threads(5);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        print_thread_id(id);
    }

    return 0;
}

/**
 * Hello world for threads
 * @param val thread number
 */
void print_thread_id(int val)
{
    printf("Hello world from therad %d\n", val);
}