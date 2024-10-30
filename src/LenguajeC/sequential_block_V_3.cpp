// Implementación del algoritmo V.3 Sequential block



#include <vector>
#include "utils.h"
std::vector<std::vector<int>> block_matrix_mult_V_3(const std::vector<std::vector<int>>& A, 
                                                      const std::vector<std::vector<int>>& B, 
                                                      int block_size) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; i += block_size) {
        for (int j = 0; j < n; j += block_size) {
            for (int k = 0; k < n; k += block_size) {
                // Definir los límites de los bloques
                int i_end = std::min(i + block_size, n);
                int j_end = std::min(j + block_size, n);
                int k_end = std::min(k + block_size, n);

                // Crear bloques temporales para mejorar la localidad de caché
                std::vector<std::vector<int>> A_block(i_end - i, std::vector<int>(k_end - k));
                std::vector<std::vector<int>> B_block(k_end - k, std::vector<int>(j_end - j));
                std::vector<std::vector<int>> C_block(i_end - i, std::vector<int>(j_end - j, 0));

                // Copiar bloques
                for (int ii = 0; ii < i_end - i; ++ii) {
                    for (int kk = 0; kk < k_end - k; ++kk) {
                        A_block[ii][kk] = A[i + ii][k + kk];
                    }
                }
                for (int kk = 0; kk < k_end - k; ++kk) {
                    for (int jj = 0; jj < j_end - j; ++jj) {
                        B_block[kk][jj] = B[k + kk][j + jj];
                    }
                }

                // Multiplicar los bloques
                for (int ii = 0; ii < i_end - i; ++ii) {
                    for (int jj = 0; jj < j_end - j; ++jj) {
                        for (int kk = 0; kk < k_end - k; ++kk) {
                            C_block[ii][jj] += A_block[ii][kk] * B_block[kk][jj];
                        }
                    }
                }

                // Actualizar el resultado
                for (int ii = 0; ii < i_end - i; ++ii) {
                    for (int jj = 0; jj < j_end - j; ++jj) {
                        C[i + ii][j + jj] += C_block[ii][jj];
                    }
                }
            }
        }
    }
    return C;
}
