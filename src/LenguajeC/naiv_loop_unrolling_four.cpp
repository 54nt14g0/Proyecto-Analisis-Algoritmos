// naiv_loop_unrolling_four.cpp
#include <vector>
#include "utils.h"

std::vector<std::vector<int>> naiv_loop_unrolling_four(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int sum = 0;
            for (int k = 0; k < n; k += 4) {
                sum += A[i][k] * B[k][j];
                if (k + 1 < n) sum += A[i][k + 1] * B[k + 1][j];
                if (k + 2 < n) sum += A[i][k + 2] * B[k + 2][j];
                if (k + 3 < n) sum += A[i][k + 3] * B[k + 3][j];
            }
            C[i][j] = sum;
        }
    }
    return C;
}
