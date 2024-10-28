import numpy as np

def block_matrix_mult_IV_3(A, B, block_size):
    """
    Implementación del algoritmo IV.3 Sequential block
    Multiplica matrices dividiendo A en bloques verticales y B en bloques horizontales
    """
    n = len(A)
    C = np.zeros((n, n))
    
    for i in range(0, n, block_size):
        for j in range(0, n, block_size):
            for k in range(0, n, block_size):
                # Definir los límites de los bloques
                i_end = min(i + block_size, n)
                j_end = min(j + block_size, n)
                k_end = min(k + block_size, n)
                
                # Multiplicar los bloques
                for kk in range(k, k_end):
                    for ii in range(i, i_end):
                        for jj in range(j, j_end):
                            C[ii][jj] += A[ii][kk] * B[kk][jj]
    return C
