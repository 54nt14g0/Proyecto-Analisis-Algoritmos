// strassen_winograd.cpp

#include "utils.h"

#include <vector>
using namespace std;


vector<vector<int>> strassen_winograd(const vector<vector<int>>& A, const vector<vector<int>>& B) {
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

    // Dividir las matrices
    int mid = n / 2;
    vector<vector<int>> A11(mid, vector<int>(mid)), A12(mid, vector<int>(mid)),
                        A21(mid, vector<int>(mid)), A22(mid, vector<int>(mid));
    vector<vector<int>> B11(mid, vector<int>(mid)), B12(mid, vector<int>(mid)),
                        B21(mid, vector<int>(mid)), B22(mid, vector<int>(mid));

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

    // Calcular factores intermedios
    vector<vector<int>> S1 = subtract(B12, B22);
    vector<vector<int>> S2 = add(A11, A12);
    vector<vector<int>> S3 = add(A21, A22);
    vector<vector<int>> S4 = subtract(B21, B11);
    vector<vector<int>> S5 = add(A11, A22);
    vector<vector<int>> S6 = add(B11, B22);
    vector<vector<int>> S7 = subtract(A12, A22);
    vector<vector<int>> S8 = add(B21, B22);
    vector<vector<int>> S9 = subtract(A11, A21);
    vector<vector<int>> S10 = add(B11, B12);

    // Subproductos
    vector<vector<int>> P1 = strassen_winograd(A11, S1);
    vector<vector<int>> P2 = strassen_winograd(S2, B22);
    vector<vector<int>> P3 = strassen_winograd(S3, B11);
    vector<vector<int>> P4 = strassen_winograd(A22, S4);
    vector<vector<int>> P5 = strassen_winograd(S5, S6);
    vector<vector<int>> P6 = strassen_winograd(S7, S8);
    vector<vector<int>> P7 = strassen_winograd(S9, S10);

    // Combinar resultados
    vector<vector<int>> C11 = add(subtract(add(P5, P4), P2), P6);
    vector<vector<int>> C12 = add(P1, P2);
    vector<vector<int>> C21 = add(P3, P4);
    vector<vector<int>> C22 = subtract(subtract(add(P5, P1), P3), P7);

    // Ensamblar matriz resultado
    vector<vector<int>> C(n, vector<int>(n));
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
