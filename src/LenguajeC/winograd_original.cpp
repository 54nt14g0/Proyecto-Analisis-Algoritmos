// winograd_original.cpp
#include <vector>
#include "utils.h"

std::vector<std::vector<int>> winograd_original(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));
    std::vector<int> row_factor(n);
    std::vector<int> col_factor(n);

    for (int i = 0; i < n; ++i) {
        row_factor[i] = 0;
        for (int j = 0; j < n - 1; ++j) {
            row_factor[i] += A[i][j] * B[j + 1][0];
        }
    }

    for (int j = 0; j < n; ++j) {
        col_factor[j] = 0;
        for (int i = 0; i < n - 1; ++i) {
            col_factor[j] += A[0][i + 1] * B[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = row_factor[i] * col_factor[j];
        }
    }
    return C;
}
