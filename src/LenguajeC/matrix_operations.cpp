#include <vector>
#include <stdexcept> // Para manejar excepciones

#include "utils.h"

// Implementación de la función add
std::vector<std::vector<int>> add(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    // Verificar que las matrices A y B no estén vacías y tengan el mismo tamaño
    if (A.empty() || B.empty() || A.size() != B.size() || A[0].size() != B[0].size()) {
        throw std::invalid_argument("Las matrices deben tener el mismo tamaño y no estar vacías.");
    }

    int rows = A.size(); // Número de filas
    int cols = A[0].size(); // Número de columnas
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0)); // Inicializar matriz resultado

    // Realizar la suma de las matrices
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = A[i][j] + B[i][j]; // Sumar los elementos correspondientes
        }
    }
    return result; // Devolver la matriz resultante
}

// Implementación de la función subtract
std::vector<std::vector<int>> subtract(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    // Verificar que las matrices A y B no estén vacías y tengan el mismo tamaño
    if (A.empty() || B.empty() || A.size() != B.size() || A[0].size() != B[0].size()) {
        throw std::invalid_argument("Las matrices deben tener el mismo tamaño y no estar vacías.");
    }

    int rows = A.size(); // Número de filas
    int cols = A[0].size(); // Número de columnas
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0)); // Inicializar matriz resultado

    // Realizar la resta de las matrices
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = A[i][j] - B[i][j]; // Restar los elementos correspondientes
        }
    }
    return result; // Devolver la matriz resultante
}
