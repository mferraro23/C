// -------------------- RESULTS --------------------
// For a matrix of size 64x64 the elapsed cpu time is 0.000000 microseconds
// For a matrix of size 128x128 the elapsed cpu time is 4,000.000000 microseconds
// For a matrix of size 256x256 the elapsed cpu time is 35,000.000000 microseconds
// For a matruix of size 512x512 the elapsed cpu time is 391,000.000000 microseconds
// For a matrix of size 1024x1024 the elapsed cpu time is 3,310,000.000000 microseconds
//
// 4.) The Big O notation for this algorithm is O(n^3) results of the runtime are above.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXVAL 1227
#define MATRIXSIZE 590
#define NUMELEMENTS MATRIXSIZE *MATRIXSIZE
#ifndef MAXMATRIXSIZE
#define MAXMATRIX 1024
#define MAXMATRIXSIZE MAXMATRIX *MAXMATRIX
#endif
/* #define NUMELEMENTS 349240  about 590.8 ^2 */

void dgemm(int n, double *A, double *B, double *C);
void matrixFiller(int size, double *matrix);
void emptyMatrix(int size, double *matrix);

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: ./program <matrix size> <random seed>\n"); // same except we are using command line arguments to pass in the matrix size and random seed
        return 1;
    }
    int matrix_size = atoi(argv[1]);
    int random_seed = atoi(argv[2]);

    clock_t start, end;
    double cpu_time_used;
    srand(random_seed);

    double *A1 = malloc(matrix_size * matrix_size * sizeof(double));
    double *B1 = malloc(matrix_size * matrix_size * sizeof(double));
    double *C1 = malloc(matrix_size * matrix_size * sizeof(double));

    matrixFiller(matrix_size * matrix_size, A1);
    matrixFiller(matrix_size * matrix_size, B1);
    emptyMatrix(matrix_size * matrix_size, C1);

    start = clock();
    printf("About to DGEMM large matrix \n");
    dgemm(matrix_size, A1, B1, C1);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("The elapsed cpu time is %lf microseconds\n", cpu_time_used * 1e6);
    printf("The first twenty values from matrix C are:\n");
    for (int i = 0; i < 20; i++)
    {
        printf("%d. %f\n", i + 1, C1[i]);
    }

    free(A1);
    free(B1);
    free(C1);
    return 0;
}

void dgemm(int n, double *A, double *B, double *C)
{
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
            {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

void matrixFiller(int size, double *matrix)
{
    int i;
    for (i = 0; i < size; i++)
    {
        matrix[i] = (double)rand() / (double)RAND_MAX;
    }
}

void emptyMatrix(int size, double *matrix)
{
    int i;
    for (i = 0; i < size; i++)
    {
        matrix[i] = 0;
    }
}

