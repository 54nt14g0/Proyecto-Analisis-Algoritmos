import numpy as np

def winograd_original(A, B):
    """
    Implementación correcta del algoritmo de Winograd
    """
    m, n = A.shape
    r = B.shape[1]
    
    # Precálculo de productos por fila (elementos adyacentes en A)
    row_factor = np.zeros(m)
    for i in range(m):
        for j in range(n//2):
            row_factor[i] += A[i,2*j] * A[i,2*j+1]
    
    # Precálculo de productos por columna (elementos adyacentes en B)
    col_factor = np.zeros(r)
    for i in range(r):
        for j in range(n//2):
            col_factor[i] += B[2*j,i] * B[2*j+1,i]
    
    # Cálculo de la matriz resultante usando la fórmula de Winograd
    C = np.zeros((m, r))
    for i in range(m):
        for j in range(r):
            # Inicializa con los factores negativos
            C[i,j] = -row_factor[i] - col_factor[j]
            
            # Aplica la fórmula de Winograd para cada par
            for k in range(n//2):
                C[i,j] += (A[i,2*k] + B[2*k+1,j]) * (A[i,2*k+1] + B[2*k,j])

    # Ajuste para dimensión impar
    if n % 2 == 1:
        for i in range(m):
            for j in range(r):
                C[i,j] += A[i,n-1] * B[n-1,j]
    
    return C
