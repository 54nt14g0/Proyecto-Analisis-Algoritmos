import numpy as np

def winograd_original(A, B):
    n = A.shape[0]
    C = np.zeros((n, n), dtype=int)
    row_factor = np.zeros(n)
    col_factor = np.zeros(n)

    for i in range(n):
        row_factor[i] = sum(A[i][j] * B[j][0] for j in range(n - 1))

    for j in range(n):
        col_factor[j] = sum(A[0][i] * B[i][j] for i in range(n - 1))

    for i in range(n):
        for j in range(n):
            C[i][j] = row_factor[i] + col_factor[j]

    return C
