import numpy as np

import numpy as np

def strassen_winograd(A, B):
    n = len(A)
    
    # Caso base
    if n <= 2:
        return np.dot(A, B)
    
    # Dividir matrices en submatrices
    mid = n // 2
    A11, A12 = A[:mid, :mid], A[:mid, mid:]
    A21, A22 = A[mid:, :mid], A[mid:, mid:]
    B11, B12 = B[:mid, :mid], B[:mid, mid:]
    B21, B22 = B[mid:, :mid], B[mid:, mid:]
    
    # Precomputaciones de Strassen-Winograd
    S1 = B12 - B22
    S2 = A11 + A12
    S3 = A21 + A22
    S4 = B21 - B11
    S5 = A11 + A22
    S6 = B11 + B22
    S7 = A12 - A22
    S8 = B21 + B22
    S9 = A11 - A21
    S10 = B11 + B12

    # Calcular productos intermedios
    P1 = strassen_winograd(A11, S1)
    P2 = strassen_winograd(S2, B22)
    P3 = strassen_winograd(S3, B11)
    P4 = strassen_winograd(A22, S4)
    P5 = strassen_winograd(S5, S6)
    P6 = strassen_winograd(S7, S8)
    P7 = strassen_winograd(S9, S10)

    # Calcular submatrices de C
    C11 = P5 + P4 - P2 + P6
    C12 = P1 + P2
    C21 = P3 + P4
    C22 = P5 + P1 - P3 - P7

    # Combinar cuadrantes
    C_top = np.hstack((C11, C12))
    C_bottom = np.hstack((C21, C22))
    C = np.vstack((C_top, C_bottom))
    
    return C


