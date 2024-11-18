import numpy as np

def winograd_scaled(A, B):
    """
    Implementación correcta del algoritmo Winograd Scaled
    """
    m, n = A.shape
    r = B.shape[1]
    
    # Normalizar la escala de los elementos para evitar desbordamiento
    scale_A = np.max(np.abs(A))
    scale_B = np.max(np.abs(B))
    
    if scale_A > 0:
        A = A / scale_A
    if scale_B > 0:
        B = B / scale_B
    
    # Precálculo de productos por fila
    row_factor = np.zeros(m)
    for i in range(m):
        for j in range(n//2):
            row_factor[i] += A[i,2*j] * A[i,2*j+1]
    
    # Precálculo de productos por columna
    col_factor = np.zeros(r)
    for i in range(r):
        for j in range(n//2):
            col_factor[i] += B[2*j,i] * B[2*j+1,i]
    
    # Cálculo de la matriz resultante
    C = np.zeros((m, r))
    for i in range(m):
        for j in range(r):
            C[i,j] = -row_factor[i] - col_factor[j]
            for k in range(n//2):
                C[i,j] += (A[i,2*k] + B[2*k+1,j]) * (A[i,2*k+1] + B[2*k,j])
    
    # Ajuste para dimensión impar
    if n % 2 == 1:
        for i in range(m):
            for j in range(r):
                C[i,j] += A[i,n-1] * B[n-1,j]
    
    # Reajustar la escala
    return C * scale_A * scale_B