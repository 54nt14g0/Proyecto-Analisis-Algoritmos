#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <sstream>
#include <string>
#include <iomanip> // Para setprecision y fixed
#include "utils.h"
using namespace std;

// Función para leer una matriz desde un archivo
vector<vector<int>> read_matrix(const string &filename) {
    ifstream infile(filename);
    vector<vector<int>> matrix;
    string line;

    while (getline(infile, line)) {
        vector<int> row;
        int num;
        stringstream ss(line);
        while (ss >> num) {
            row.push_back(num);
            if (ss.peek() == ',') ss.ignore(); // Ignora la coma
        }
        matrix.push_back(row);
    }
    return matrix;
}

// Función para escribir los tiempos de ejecución en un archivo y mostrar en consola
void log_execution_time(const string &filename, const string &algorithm, const string &matrix_size, double duration) {
    // Guardar en archivo
    ofstream outfile(filename, ios::app); // Abrir en modo de añadir
    outfile << algorithm << " para tamanio " << matrix_size << ": " 
            << fixed << setprecision(6) << duration << " segundos" << endl;
    
    // Mostrar en consola
    cout << algorithm << " para tamanio " << matrix_size << ": " 
         << fixed << setprecision(6) << duration << " segundos" << endl;
}

// Función para obtener el tamaño de la matriz en formato "NxN"
string get_matrix_size(const vector<vector<int>>& matrix) {
    int size = matrix.size(); // Suponiendo que las matrices son cuadradas
    return to_string(size) + "x" + to_string(size);
}

// Función para ejecutar todos los algoritmos con diferentes tamaños de matriz
void execute_algorithms(const vector<string> &matrix_files_a, const vector<string> &matrix_files_b, const string &tiempos_path) {
    size_t num_files = matrix_files_a.size();
    for (size_t i = 0; i < num_files; ++i) {
        // Leer la matriz A
        auto A = read_matrix(matrix_files_a[i]);
        // Leer la matriz B
        auto B = read_matrix(matrix_files_b[i]);
        
        // Obtener el tamaño de la matriz para la salida
        string matrix_size = get_matrix_size(A);

        // Avisar en consola que se procesará el siguiente tamaño de matriz
        cout << "\nProcesando algoritmos para matrices de tamanio " << matrix_size << "...\n" << endl;

        // Medir el tiempo de ejecución de cada algoritmo
        auto start = chrono::high_resolution_clock::now();
        auto C1 = naiv_on_array(A, B);
        auto end = chrono::high_resolution_clock::now();
        log_execution_time(tiempos_path, "Naive On Array", matrix_size, chrono::duration<double>(end - start).count());

        start = chrono::high_resolution_clock::now();
        auto C2 = naiv_loop_unrolling_two(A, B);
        end = chrono::high_resolution_clock::now();
        log_execution_time(tiempos_path, "Naive Loop Unrolling Two", matrix_size, chrono::duration<double>(end - start).count());

        start = chrono::high_resolution_clock::now();
        auto C3 = naiv_loop_unrolling_four(A, B);
        end = chrono::high_resolution_clock::now();
        log_execution_time(tiempos_path, "Naive Loop Unrolling Four", matrix_size, chrono::duration<double>(end - start).count());

        start = chrono::high_resolution_clock::now();
        auto C4 = winograd_original(A, B);
        end = chrono::high_resolution_clock::now();
        log_execution_time(tiempos_path, "Winograd Original", matrix_size, chrono::duration<double>(end - start).count());

        start = chrono::high_resolution_clock::now();
        auto C5 = winograd_scaled(A, B);
        end = chrono::high_resolution_clock::now();
        log_execution_time(tiempos_path, "Winograd Scaled", matrix_size, chrono::duration<double>(end - start).count());

        start = chrono::high_resolution_clock::now();
        auto C6 = strassen_naiv(A, B);
        end = chrono::high_resolution_clock::now();
        log_execution_time(tiempos_path, "Strassen Naive", matrix_size, chrono::duration<double>(end - start).count());

        start = chrono::high_resolution_clock::now();
        auto C7 = strassen_winograd(A, B);
        end = chrono::high_resolution_clock::now();
        log_execution_time(tiempos_path, "Strassen Winograd", matrix_size, chrono::duration<double>(end - start).count());

        start = chrono::high_resolution_clock::now();
        auto C8 = block_matrix_mult_III_3(A, B, 2);
        end = chrono::high_resolution_clock::now();
        log_execution_time(tiempos_path, "Block Matrix Mult III.3", matrix_size, chrono::duration<double>(end - start).count());

        start = chrono::high_resolution_clock::now();
        auto C9 = block_matrix_mult_IV_3(A, B, 2);
        end = chrono::high_resolution_clock::now();
        log_execution_time(tiempos_path, "Block Matrix Mult IV.3", matrix_size, chrono::duration<double>(end - start).count());

        start = chrono::high_resolution_clock::now();
        auto C10 = block_matrix_mult_V_3(A, B, 2);
        end = chrono::high_resolution_clock::now();
        log_execution_time(tiempos_path, "Block Matrix Mult V.3", matrix_size, chrono::duration<double>(end - start).count());

        // Avisar al usuario que se procederá con el siguiente tamaño de matriz
        cout << "\nCompletado para tamanio " << matrix_size << ". Procediendo con el siguiente tamanio...\n" << endl;
    }
}

int main() {
    // Rutas de las matrices A
    vector<string> matrix_files_a = {
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_a_2x2.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_a_4x4.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_a_8x8.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_a_16x16.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_a_32x32.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_a_64x64.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_a_128x128.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_a_256x256.txt"
    };

    // Rutas de las matrices B
    vector<string> matrix_files_b = {
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_b_2x2.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_b_4x4.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_b_8x8.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_b_16x16.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_b_32x32.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_b_64x64.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_b_128x128.txt",
        "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\matriz_b_256x256.txt"
    };

    string tiempos_path = "C:\\Users\\ljane\\Downloads\\Proyecto-Analisis-Algoritmos\\guardadoTiempos\\tiempos_ejecucion_c.txt";

    // Ejecutar algoritmos para cada par de matrices
    execute_algorithms(matrix_files_a, matrix_files_b, tiempos_path);

    return 0;
}
