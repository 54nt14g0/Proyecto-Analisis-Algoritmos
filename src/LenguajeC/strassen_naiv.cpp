// strassen_naiv.cpp
#include <vector>
#include "utils.h"

#include <bits/stdc++.h>
using namespace std;

// Implementación del algoritmo de Strassen

vector<vector<int>> strassen_naiv(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    // Caso base
    if (n <= 2) {
        vector<vector<int>> C(n, vector<int>(n, 0));
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
    vector<vector<int>> A11(mid, vector<int>(mid)), A12(mid, vector<int>(mid)), A21(mid, vector<int>(mid)), A22(mid, vector<int>(mid));
    vector<vector<int>> B11(mid, vector<int>(mid)), B12(mid, vector<int>(mid)), B21(mid, vector<int>(mid)), B22(mid, vector<int>(mid));

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

    // P1 a P7
    auto subtract = [](const vector<vector<int>>& A, const vector<vector<int>>& B) {
        int n = A.size();
        vector<vector<int>> C(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = A[i][j] - B[i][j];
            }
        }
        return C;
    };

    auto add = [](const vector<vector<int>>& A, const vector<vector<int>>& B) {
        int n = A.size();
        vector<vector<int>> C(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
        return C;
    };

    vector<vector<int>> P1 = strassen_naiv(A11, subtract(B12, B22));
    vector<vector<int>> P2 = strassen_naiv(add(A11, A12), B22);
    vector<vector<int>> P3 = strassen_naiv(add(A21, A22), B11);
    vector<vector<int>> P4 = strassen_naiv(A22, subtract(B21, B11));
    vector<vector<int>> P5 = strassen_naiv(add(A11, A22), add(B11, B22));
    vector<vector<int>> P6 = strassen_naiv(subtract(A12, A22), add(B21, B22));
    vector<vector<int>> P7 = strassen_naiv(subtract(A11, A21), add(B11, B12));

    // Resultados C11, C12, C21, C22
    vector<vector<int>> C11 = add(subtract(add(P5, P4), P2), P6);
    vector<vector<int>> C12 = add(P1, P2);
    vector<vector<int>> C21 = add(P3, P4);
    vector<vector<int>> C22 = subtract(subtract(add(P5, P1), P3), P7);

    // Combinar submatrices para obtener la matriz final C
    vector<vector<int>> C(n, vector<int>(n, 0));

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