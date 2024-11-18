import numpy as np

def naiv_loop_unrolling_four(A, B):
    # Determinar las dimensiones de las matrices
    n = len(A)          # Número de filas de A
    m = len(A[0])       # Número de columnas de A (y filas de B)
    p = len(B[0])       # Número de columnas de B

    # Inicializar la matriz resultante con ceros
    C = [[0 for _ in range(p)] for _ in range(n)]

    # Multiplicación con desenrollado de bucles (procesando 4 elementos a la vez)
    for i in range(n):  # Filas de A
        for j in range(p):  # Columnas de B
            # Procesar los elementos de cuatro en cuatro
            for k in range(0, m - 3, 4):  # Hasta m-3, procesando bloques de tamaño 4
                C[i][j] += (
                    A[i][k] * B[k][j] +
                    A[i][k + 1] * B[k + 1][j] +
                    A[i][k + 2] * B[k + 2][j] +
                    A[i][k + 3] * B[k + 3][j]
                )
            # Procesar los elementos restantes si m no es múltiplo de 4
            for k in range(m - (m % 4), m):  # Desde el último múltiplo de 4 hasta m
                C[i][j] += A[i][k] * B[k][j]

    return C

