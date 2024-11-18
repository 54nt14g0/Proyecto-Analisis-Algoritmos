import numpy as np

def naiv_on_array(A, B):
    # Se obtienen las dimensiones de las matrices
    m = len(A)         # Número de filas de la matriz A
    n = len(A[0])      # Número de columnas de la matriz A (y filas de la matriz B)
    p = len(B[0])      # Número de columnas de la matriz B

    # Se inicializa la matriz resultante C con ceros
    # C tiene dimensiones m x p
    C = [[0 for _ in range(p)] for _ in range(m)]

    # Se realizan los cálculos para la multiplicación de matrices
    for i in range(m):             # Itera sobre cada fila de A
        for j in range(p):         # Itera sobre cada columna de B
            for k in range(n):     # Itera sobre los elementos de la fila de A y columna de B
                # Acumula el producto de A[i][k] y B[k][j] en C[i][j]
                C[i][j] += A[i][k] * B[k][j]

    # Se retorna la matriz resultante C
    return C
