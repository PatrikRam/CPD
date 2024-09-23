#include <stdio.h>
#include <time.h>

#define MAX 1000

void first_loop(double A[MAX][MAX], double x[MAX], double y[MAX]) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
}

void second_loop(double A[MAX][MAX], double x[MAX], double y[MAX]) {
    for (int j = 0; j < MAX; j++) {
        for (int i = 0; i < MAX; i++) {
            y[i] += A[i][j] * x[j];
        }
    }
}

int main() {
    double A[MAX][MAX];
    double x[MAX];
    double y[MAX];

   
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            A[i][j] = i + j;  
        }
    }

    for (int i = 0; i < MAX; i++) {
        x[i] = 1;  
    }

    for (int i = 0; i < MAX; i++) {
        y[i] = 0;  
    }

    clock_t start, end;
    double cpu_time_used;

   
    start = clock();
    first_loop(A, x, y);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo del primer bucle: %f segundos\n", cpu_time_used);

   
    for (int i = 0; i < MAX; i++) y[i] = 0;

   
    start = clock();
    second_loop(A, x, y);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo del segundo bucle: %f segundos\n", cpu_time_used);

    return 0;
}



