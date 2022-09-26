import numpy as np


def submat(matrix):
    row, col = matrix.shape
    row2, col2 = row//2, col//2
    return matrix[:row2, :col2], matrix[:row2, col2:], matrix[row2:, :col2], matrix[row2:, col2:]


def strassen(x, y):

    if len(x) == 1:
        return x * y
    a, b, c, d = submat(x)
    e, f, g, h = submat(y)

    m1 = strassen(a, f - h)
    m2 = strassen(a + b, h)
    m3 = strassen(c + d, e)
    m4 = strassen(d, g - e)
    m5 = strassen(a + d, e + h)
    m6 = strassen(b - d, g + h)
    m7 = strassen(a - c, e + f)

    c11 = m5 + m4 - m2 + m6
    c12 = m1 + m2
    c21 = m3 + m4
    c22 = m1 + m5 - m3 - m7

    c = np.vstack((np.hstack((c11, c12)), np.hstack((c21, c22))))

    return c


A = []
r1 = int(input("enter order of matrix::row: "))
c1 = int(input("enter order of matrix::column: "))
print("enter values:")
for i in range(r1):
    l = []
    for j in range(c1):
        l.append(int(input()))
    A.append(l)
B = []
r2 = int(input("enter order of matrix::row: "))
c2 = int(input("enter order of matrix::column: "))
print("enter values:")
for i in range(r2):  # A for loop for row entries
    l = []
    for j in range(c2):  # A for loop for column entries
        l.append(int(input()))
    B.append(l)
a = np.array(A)
b = np.array(B)
if c1 == r2:
    print("result matrix")
    print(strassen(a, b))
else:
    print("cannot do operation")
