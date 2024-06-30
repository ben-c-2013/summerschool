#include <cstdio>

#define NX 102400

int main(void)
{
    long vecA[NX];
    long sum, psum, sumex;
    int i;

    /* Initialization of the vectors */
    for (i = 0; i < NX; i++) {
        vecA[i] = (long) i + 1;
    }

    sumex = (long) NX * (NX + 1) / ((long) 2);
    printf("Arithmetic sum formula (exact):                  %ld\n",
           sumex);

    sum = 0.0;
    /* Version with data race */
    #pragma omp parallel for default(shared) private(i)
    for (i = 0; i < NX; i++) {
        #pragma omp critical  // A section that is executed by only one thread at a time.
        {
            sum += vecA[i];
        }
    }
    printf("Sum with data race:                              %ld\n",
           sum);

    return 0;
}
