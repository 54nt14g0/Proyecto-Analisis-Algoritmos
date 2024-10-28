import numpy as np

def naiv_loop_unrolling_two(A, B):
    n = A.shape[0]
    C = np.zeros((n, n), dtype=int)
    for i in range(n):
        for j in range(n):
            sum1 = 0
            sum2 = 0
            for k in range(0, n, 2):
                sum1 += A[i][k] * B[k][j]
                if k + 1 < n:
                    sum2 += A[i][k + 1] * B[k + 1][j]
            C[i][j] = sum1 + sum2
    return C
