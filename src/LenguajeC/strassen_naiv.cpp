// strassen_naiv.cpp
#include <vector>
#include "utils.h"

#include <bits/stdc++.h>
using namespace std;

// Implementación del algoritmo de Strassen


#include <iostream>
#include <vector>
using namespace std;

using Matrix = vector<vector<int>>;

Matrix strassen_naiv(const Matrix& A, const Matrix& B) {
    int n = A.size();

    // Caso base
    if (n <= 2) {
        Matrix C(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }

    // Dividir las matrices en submatrices
    int mid = n / 2;
    Matrix A11(mid, vector<int>(mid)), A12(mid, vector<int>(mid)), A21(mid, vector<int>(mid)), A22(mid, vector<int>(mid));
    Matrix B11(mid, vector<int>(mid)), B12(mid, vector<int>(mid)), B21(mid, vector<int>(mid)), B22(mid, vector<int>(mid));

    // Llenar las submatrices de A y B
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    // Calcular los productos intermedios (P1 a P7)
    Matrix P1 = strassen_naiv(A11, subtract(B12, B22));
    Matrix P2 = strassen_naiv(add(A11, A12), B22);
    Matrix P3 = strassen_naiv(add(A21, A22), B11);
    Matrix P4 = strassen_naiv(A22, subtract(B21, B11));
    Matrix P5 = strassen_naiv(add(A11, A22), add(B11, B22));
    Matrix P6 = strassen_naiv(subtract(A12, A22), add(B21, B22));
    Matrix P7 = strassen_naiv(subtract(A11, A21), add(B11, B12));

    // Resultados C11, C12, C21, C22
    Matrix C11 = add(subtract(add(P5, P4), P2), P6);
    Matrix C12 = add(P1, P2);
    Matrix C21 = add(P3, P4);
    Matrix C22 = subtract(subtract(add(P5, P1), P3), P7);

    // Combinar submatrices para obtener la matriz final C
    Matrix C(n, vector<int>(n, 0));

    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }

    return C;
}