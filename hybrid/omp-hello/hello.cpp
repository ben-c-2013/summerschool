#include <cstdio>
#include <omp.h>
int main()
{
    printf("Hello world!\n");
#pragma omp parallel
    {
        printf("X\n");
    }
    return 0;
}

// Compile with `cc -fopenmp hello.cpp -o omp_hello.exe` to enable openMP.