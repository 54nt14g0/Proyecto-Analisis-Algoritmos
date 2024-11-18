import numpy as np

def block_matrix_mult_III_3(matrix_A, matrix_B,block_size):
    # Obtener las dimensiones de las matrices    
    rows_A = len(matrix_A)
    cols_B = len(matrix_B[0])
    cols_A = len(matrix_A[0])
            
    # Inicializar la matriz resultante
    result = [[0 for _ in range(cols_B)] for _ in range(rows_A)]    
    # Tamaño de los bloques
    block_size = min(rows_A, cols_B, cols_A) // 2

    
    # Multiplicar las matrices por bloques
    for row_block in range(0, rows_A, block_size):
        for col_block in range(0, cols_B, block_size):
            for col_A_block in range(0, cols_A, block_size):
                for row in range(row_block, min(row_block + block_size, rows_A)):
                    for col in range(col_block, min(col_block + block_size, cols_B)):
                        for col_A in range(col_A_block, min(col_A_block + block_size, cols_A)):
                            result[row][col] += matrix_A[row][col_A] * matrix_B[col_A][col]
    return result



