import numpy as np

def winograd_scaled(A, B):
    n = A.shape[0]
    C = np.zeros((n, n), dtype=np.int64)  # Usar np.int64 para evitar desbordamiento
    row_factor = np.zeros(n, dtype=np.int64)  # Asegurarse de que row_factor sea np.int64
    col_factor = np.zeros(n, dtype=np.int64)  # Asegurarse de que col_factor sea np.int64

    # Calcular los factores de fila
    for i in range(n):
        row_factor[i] = sum(A[i][j] * B[j][0] for j in range(n))  # Cambiar n-1 a n

    # Calcular los factores de columna
    for j in range(n):
        col_factor[j] = sum(A[0][i] * B[i][j] for i in range(n))  # Cambiar n-1 a n

    # Multiplicar los factores para obtener la matriz C
    for i in range(n):
        for j in range(n):
            C[i][j] = row_factor[i] * col_factor[j]

    return C
