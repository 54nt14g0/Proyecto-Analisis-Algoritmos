// naiv_loop_unrolling_two.cpp
#include <vector>
#include "utils.h"

std::vector<std::vector<int>> naiv_loop_unrolling_two(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int sum1 = 0, sum2 = 0;
            for (int k = 0; k < n; k += 2) {
                sum1 += A[i][k] * B[k][j];
                if (k + 1 < n) {
                    sum2 += A[i][k + 1] * B[k + 1][j];
                }
            }
            C[i][j] = sum1 + sum2;
        }
    }
    return C;
}
