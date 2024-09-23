#include <iostream>
#include <ctime>  // Para medir el tiempo
#include <cstdlib>  // Para generar n�meros aleatorios

using namespace std;

// Funci�n para multiplicar matrices cl�sicamente
void multiplyMatricesClassic(double** A, double** B, double** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Funci�n para multiplicar matrices por bloques
void multiplyMatricesBlock(double** A, double** B, double** C, int n, int blockSize) {
    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            for (int k = 0; k < n; k += blockSize) {
                // Multiplicar submatrices
                for (int ii = i; ii < i + blockSize && ii < n; ii++) {
                    for (int jj = j; jj < j + blockSize && jj < n; jj++) {
                        for (int kk = k; kk < k + blockSize && kk < n; kk++) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

// Funci�n para inicializar matrices con valores aleatorios
void initializeMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 100;  // Inicializar con valores aleatorios
        }
    }
}

// Funci�n para liberar la memoria de la matriz
void freeMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    srand(time(0));  // Semilla para generar n�meros aleatorios

    int sizes[] = {100, 200, 300, 500};  // Tama�os de las matrices a evaluar
    int blockSize = 50;  // Tama�o del bloque para la multiplicaci�n por bloques

    for (int size : sizes) {
        // Crear las matrices din�micamente
        double** A = new double*[size];
        double** B = new double*[size];
        double** C_classic = new double*[size];  // Para el m�todo cl�sico
        double** C_block = new double*[size];  // Para el m�todo por bloques
        for (int i = 0; i < size; i++) {
            A[i] = new double[size];
            B[i] = new double[size];
            C_classic[i] = new double[size];
            C_block[i] = new double[size];
        }

        // Inicializar las matrices A y B con valores aleatorios
        initializeMatrix(A, size);
        initializeMatrix(B, size);

        // Inicializar las matrices C a 0
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                C_classic[i][j] = 0;
                C_block[i][j] = 0;
            }
        }

        // Medir el tiempo de la multiplicaci�n de matrices cl�sica
        clock_t start = clock();
        multiplyMatricesClassic(A, B, C_classic, size);
        clock_t end = clock();
        double elapsed_classic = double(end - start) / CLOCKS_PER_SEC;
        cout << "Tiempo para multiplicar matrices cl�sicas de tama�o " << size << "x" << size << ": " << elapsed_classic << " segundos" << endl;

        // Medir el tiempo de la multiplicaci�n de matrices por bloques
        start = clock();
        multiplyMatricesBlock(A, B, C_block, size, blockSize);
        end = clock();
        double elapsed_block = double(end - start) / CLOCKS_PER_SEC;
        cout << "Tiempo para multiplicar matrices por bloques de tama�o " << size << "x" << size << " (bloque de " << blockSize << "): " << elapsed_block << " segundos" << endl;

        // Liberar la memoria de las matrices
        freeMatrix(A, size);
        freeMatrix(B, size);
        freeMatrix(C_classic, size);
        freeMatrix(C_block, size);

        cout << endl;
    }

    return 0;
}

