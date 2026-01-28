rows1 = int(input("Enter number of rows for Matrix 1: "))
matrix1 = [list(map(int, input(f"Row {i+1}: ").split())) for i in range(rows1)]

rows2 = int(input("Enter number of rows for Matrix 2: "))
matrix2 = [list(map(int, input(f"Row {i+1}: ").split())) for i in range(rows2)]

cols1 = len(matrix1[0])
if cols1 != rows2:
    print(f"Error: Columns of Matrix 1 ({cols1}) must match Rows of Matrix 2 ({rows2})")
    exit()


cols2 = len(matrix2[0])
sol = [[0 for _ in range(cols2)] for _ in range(rows1)]


for i in range(rows1):          
    for j in range(cols2):      
        for k in range(rows2):  
            sol[i][j] += matrix1[i][k] * matrix2[k][j]

print('\nResult of matrix multiplication:')
for row in sol:
    print(row)
