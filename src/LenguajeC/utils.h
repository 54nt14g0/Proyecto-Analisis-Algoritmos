// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

// Declaraciones de funciones
std::vector<std::vector<int>> naiv_on_array(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);
std::vector<std::vector<int>> naiv_loop_unrolling_two(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);
std::vector<std::vector<int>> naiv_loop_unrolling_four(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);
std::vector<std::vector<int>> winograd_original(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);
std::vector<std::vector<int>> winograd_scaled(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);
std::vector<std::vector<int>> strassen_naiv(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);
std::vector<std::vector<int>> strassen_winograd(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);
std::vector<std::vector<int>> block_matrix_mult_III_3(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int block_size);
std::vector<std::vector<int>> block_matrix_mult_IV_3(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int block_size);
std::vector<std::vector<int>> block_matrix_mult_V_3(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int block_size);
std::vector<std::vector<int>> add(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);
std::vector<std::vector<int>> subtract(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);

#endif // UTILS_H
