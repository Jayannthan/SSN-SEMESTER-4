def get_min_index(a):
    return a.index(min(a))


def get_col(mat, i):
    return [row[i] for row in mat]


def disp(a, R, C):
    [print("x"+str(i+1), end='\t') for i in range((C-2)//2)]
    [print("s"+str(i+1), end='\t') for i in range((C-2)//2)]
    print("z\tvalue")
    for i in range(R):
        for j in range(C):
            print(round(a[i][j], 3), end="\t")
        print("")
    print("")


def get_min_row_index(a, R, C, min_c):
    col = get_col(a, C-1)  # extracting last col
    min_col = get_col(a, min_c)
    for i in range(R-1):
        col[i] /= min_col[i]  # Step 3: Calc ratio
    return get_min_index(col[:R-1])  # min ratio


# input
C = int(input("Enter the number of variables:"))
#R = int(input("Enter the number of constraints:"))
R = C+1
C = 2*C+2
print("Enter matrix row by row:")
mat = []
for i in range(R):
    mat.append([int(j) for j in input().split()])
print("")
disp(mat, R, C)

# Step 1:Get the index of min ele in the last row
min_c = get_min_index(mat[R-1])

# Step 2:If the ele is -ve, go in otherwise end
while(mat[R-1][min_c] < 0):
    min_r = get_min_row_index(mat, R, C, min_c)
    # Step 4:pivot
    pivot = mat[min_r][min_c]

    # Step 5:making pivot as 1
    mat[min_r][:] = [x/float(pivot) for x in mat[min_r]]

    # Step 6:making other 2 rows 0
    disp(mat, R, C)
    for i in range(R):
        a = [x*mat[i][min_c] for x in mat[min_r]]
        for j in range(C):
            if i != min_r:
                mat[i][j] -= a[j]

    disp(mat, R, C)
    min_c = get_min_index(mat[R-1])

'''res = get_col(mat,C-1)
print("Value of variables: ",res)
print("Rounded Off values: ",[round(x) for x in res])'''
