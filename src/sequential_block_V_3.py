import numpy as np

def block_matrix_mult_V_3(A, B, block_size):
    """
    Implementación del algoritmo V.3 Sequential block
    Multiplica matrices dividiendo tanto A como B en bloques cuadrados
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
                
                # Copiar bloques a arrays temporales para mejor localidad de cache
                A_block = A[i:i_end, k:k_end].copy()
                B_block = B[k:k_end, j:j_end].copy()
                C_block = np.zeros((i_end - i, j_end - j))
                
                # Multiplicar los bloques
                for ii in range(i_end - i):
                    for jj in range(j_end - j):
                        for kk in range(k_end - k):
                            C_block[ii][jj] += A_block[ii][kk] * B_block[kk][jj]
                
                # Actualizar el resultado
                C[i:i_end, j:j_end] += C_block
    return C
