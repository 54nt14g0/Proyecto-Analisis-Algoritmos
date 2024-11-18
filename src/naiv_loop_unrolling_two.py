import numpy as np

def naiv_loop_unrolling_two(A, B):
    # Determinar las dimensiones de las matrices
    n = len(A)          # Número de filas de A
    m = len(A[0])       # Número de columnas de A (igual al número de filas de B)
    p = len(B[0])       # Número de columnas de B
    
    # Inicializar la matriz de resultados con ceros
    C = [[0 for _ in range(p)] for _ in range(n)]
    
    # Multiplicación con desenrollado de bucles
    for i in range(n):  # Iterar por las filas de A
        for j in range(p):  # Iterar por las columnas de B
            # Calcular el producto parcial con desenrollado
            for k in range(0, m - 1, 2):  # Procesar dos elementos por iteración
                C[i][j] += A[i][k] * B[k][j] + A[i][k + 1] * B[k + 1][j]
            # Si m es impar, procesar el último elemento
            if m % 2 != 0:
                C[i][j] += A[i][m - 1] * B[m - 1][j]
    return C