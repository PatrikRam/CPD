#include <iostream>
#include <ctime>  // Para medir el tiempo
#include <cstdlib>  // Para generar números aleatorios

using namespace std;

// Función para multiplicar matrices clásicamente
void multiplyMatrices(double** A, double** B, double** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;  // Inicializar C[i][j]
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Función para inicializar matrices con valores aleatorios
void initializeMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 100;  // Inicializar con valores aleatorios
        }
    }
}

// Función para liberar la memoria de la matriz
void freeMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    srand(time(0));  // Semilla para generar números aleatorios

    int sizes[] = {100, 200, 300, 500, 1000};  // Tamaños de las matrices a evaluar

    for (int size : sizes) {
        // Crear las matrices dinámicamente
        double** A = new double*[size];
        double** B = new double*[size];
        double** C = new double*[size];
        for (int i = 0; i < size; i++) {
            A[i] = new double[size];
            B[i] = new double[size];
            C[i] = new double[size];
        }

        // Inicializar las matrices A y B con valores aleatorios
        initializeMatrix(A, size);
        initializeMatrix(B, size);

        // Medir el tiempo de la multiplicación de matrices
        clock_t start = clock();
        multiplyMatrices(A, B, C, size);
        clock_t end = clock();

        // Calcular el tiempo en segundos
        double elapsed = double(end - start) / CLOCKS_PER_SEC;
        cout << "Tiempo para multiplicar matrices de tamaño " << size << "x" << size << ": " << elapsed << " segundos" << endl;

        // Liberar la memoria de las matrices
        freeMatrix(A, size);
        freeMatrix(B, size);
        freeMatrix(C, size);
    }

    return 0;
}

