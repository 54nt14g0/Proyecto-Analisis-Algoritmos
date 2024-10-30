// Implementación del algoritmo IV.3 Sequential block


#include <vector>
#include "utils.h"
std::vector<std::vector<int>> block_matrix_mult_IV_3(const std::vector<std::vector<int>>& A, 
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

                // Multiplicar los bloques
                for (int kk = k; kk < k_end; ++kk) {
                    for (int ii = i; ii < i_end; ++ii) {
                        for (int jj = j; jj < j_end; ++jj) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
    return C;
}
