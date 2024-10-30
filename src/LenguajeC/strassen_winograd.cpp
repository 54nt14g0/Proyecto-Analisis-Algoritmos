// strassen_winograd.cpp
#include <vector>
#include "utils.h"


// Implementación del algoritmo de Strassen con Winograd
std::vector<std::vector<int>> strassen_winograd(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    // Dividir las matrices
    int k = n / 2;
    std::vector<std::vector<int>> A11(k, std::vector<int>(k)),
                                    A12(k, std::vector<int>(k)),
                                    A21(k, std::vector<int>(k)),
                                    A22(k, std::vector<int>(k)),
                                    B11(k, std::vector<int>(k)),
                                    B12(k, std::vector<int>(k)),
                                    B21(k, std::vector<int>(k)),
                                    B22(k, std::vector<int>(k));

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    auto row_factor = std::vector<int>(k);
    auto col_factor = std::vector<int>(k);

    for (int i = 0; i < k; ++i) {
        row_factor[i] = A11[i][0] * B12[0][i];
        col_factor[i] = A12[0][i] * B21[i][0];
    }

    auto M1 = strassen_winograd(add(A11, A22), add(B11, B22));
    auto M2 = strassen_winograd(add(A21, A22), B11);
    auto M3 = strassen_winograd(A11, subtract(B12, B22));
    auto M4 = strassen_winograd(A22, subtract(B21, B11));
    auto M5 = strassen_winograd(add(A11, A12), B22);
    auto M6 = strassen_winograd(subtract(A21, A11), add(B11, B12));
    auto M7 = strassen_winograd(subtract(A12, A22), add(B21, B22));

    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    // Combinando los resultados en la matriz final C
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + k] = M3[i][j] + M5[i][j];
            C[i + k][j] = M2[i][j] + M4[i][j];
            C[i + k][j + k] = M1[i][j] + M3[i][j] - M2[i][j] + M6[i][j];
        }
    }

    return C;
}
