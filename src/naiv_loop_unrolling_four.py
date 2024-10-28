import numpy as np

def naiv_loop_unrolling_four(A, B):
    n = A.shape[0]
    C = np.zeros((n, n), dtype=int)
    for i in range(n):
        for j in range(n):
            sum0 = 0
            sum1 = 0
            sum2 = 0
            sum3 = 0
            for k in range(0, n, 4):
                sum0 += A[i][k] * B[k][j]
                if k + 1 < n:
                    sum1 += A[i][k + 1] * B[k + 1][j]
                if k + 2 < n:
                    sum2 += A[i][k + 2] * B[k + 2][j]
                if k + 3 < n:
                    sum3 += A[i][k + 3] * B[k + 3][j]
            C[i][j] = sum0 + sum1 + sum2 + sum3
    return C
