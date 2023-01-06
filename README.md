# PROJECT_MATRIX_CPP
The static library helps work with matrices using class MyMatrix in *MacOS* or *Linux OS*.

The library uses *double* data type for matrices.

### How to Compile the Library
Use the following Makefile instruction:
```bash
make my_matrix.a 
```

The static library file will be created.

### How to Use the Library
- Include header `my_matrix.h` in your code.
- Inform link editor the name of the library file and the path where it's situated during the linkage.

For example:
```bash
g++ test.cpp -L . -lmy_matrix -o test
```

### How to Create Matrix
- By default you can create empty matrix:
```cpp
MyMatrix matrix;
```
- For creating with specified size (the matrix will be filled by 0):
```cpp
MyMatrix matrix(3, 4);
```
- For creating with specified size and fillment:
```cpp
double data_massive_1[6] = {1, 2, 3, 4, 5, 6};
MyMatrix matrix(3, 4, data_massive_1);
```
- For creating using copy or move constructor:
```cpp
MyMatrix matrix_2(matrix_1);
MyMatrix matrix_3(std::move(matrix_2));
```
### How to Delete Matrix
```cpp
matrix.Clear();
```

### Other Features of the Library
- Summ of two matrices
```cpp
matrix_1.SumMatrix(matrix_2);
// OR
matrix_1 += matrix_2;
// OR
MyMatrix matrix = matrix_1 + matrix_2;
```
- Substraction of two matrices
```cpp
matrix_1.SuBMatrix(matrix_2);
// OR
matrix_1 -= matrix_2;
// OR
MyMatrix matrix = matrix_1 - matrix_2;
```
- Multiplication of the matrix and the number
```cpp
matrix_1.MulNumber(number);
// OR
matrix_1 *= number;
// OR
MyMatrix matrix = matrix_1 * number;
// OR
MyMatrix matrix = number * matrix_1;
```
- Multiplication of two matrices
```cpp
matrix_1.MulMatrix(matrix_2);
// OR
matrix_1 *= matrix_2;
// OR
MyMatrix matrix = matrix_1 * matrix_2;
```
- Matrix transposing
```cpp
MyMatrix matrix = matrix_1.Transpose();
```
- Calculation of the matrix determinate
```cpp
double dat = matrix_1.Determinate();
```
- Creation the matrix of cofactors
```cpp
MyMatrix matrix = matrix_1.CalcComplements();
```
- Creation the inverse matrix
```cpp
MyMatrix matrix = matrix_1.InverseMatrix();
```
- Comparison of two matrices
```cpp
bool res = matrix_1.EqualMatrix(matrix_2);
// OR
bool res = matrix_1 == matrix_2;
```
- Printing the matrix
```cpp
matrix_1.OutputMatrix();
```

### Overload for Using Matrix Indices
```cpp
MyMatrix matrix (3, 4);
matrix(1, 0) = 5.5;
```

### Accessors and Mutators for Matrix Rows and Cols Value
```cpp
int get_rows();
int get_cols();
void set_rows(int value_rows);
void set_cols(int value_cols);
```
