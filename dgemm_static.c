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

#define MATRIXSIZE 1024
#define NUMELEMENTS MATRIXSIZE *MATRIXSIZE
#define MAXMATRIXSIZE 1024 * 1024

void dgemm(int n, double *A, double *B, double *C);
void matrixFiller(int size, double *matrix);
void emptyMatrix(int size, double *matrix);

int main()
{
    clock_t start, end;
    double cpu_time_used;
    srand(2023);

    double *A1 = malloc(NUMELEMENTS * sizeof(double)); // malloc dynamically allocates memory, sizeof() returns the size of the data type in bytes that are needed to store the variable
    double *B1 = malloc(NUMELEMENTS * sizeof(double));
    double *C1 = malloc(NUMELEMENTS * sizeof(double));

    matrixFiller(NUMELEMENTS, A1); // O(n)
    matrixFiller(NUMELEMENTS, B1); // O(n)
    emptyMatrix(NUMELEMENTS, C1);  // O(n)

    start = clock();
    printf("About to DGEMM large matrix \n");
    dgemm(MATRIXSIZE, A1, B1, C1); // O(n^3)
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("The elapsed cpu time is %lf microseconds\n", cpu_time_used * 1e6);
    printf("The first ten values from matrix C, of size 1024x1024 are:\n");
    for (int i = 0; i < 10; i++) 
    {
        printf("%d. %f\n", i + 1, C1[i]);
    }

    free(A1); // free up the memory that was allocated by malloc
    free(B1);
    free(C1);
    return 0;
}

// matrix multiplication that takes in two matrices and multiplies them together, stores in C
void dgemm(int n, double *A, double *B, double *C) // O(n^3)
{
    for (int i = 0; i < n; i++) //O(n)
    {
        for (int j = 0; j < n; j++) // O(n)
        {
            for (int k = 0; k < n; k++) // O(n)
            {
                C[i * n + j] += A[i * n + k] * B[k * n + j]; // multiplying the matrices together, three loops are necessary to compute the dot product between each pair of rows and columns in A and B, and to sum the results
            }
        }
    }
}

// adds random numbers to the matrix
void matrixFiller(int size, double *matrix) // O(n)
{
    for (int i = 0; i < size; i++) // O(n)
    {
        matrix[i] = (double)rand() / (double)RAND_MAX;
    }
}

// fills the matrix with zeros
void emptyMatrix(int size, double *matrix) // O(n)
{
    for (int i = 0; i < size; i++) // O(n)
    {
        matrix[i] = 0;
    }
}
