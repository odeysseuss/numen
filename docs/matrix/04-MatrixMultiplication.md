## Matrix Multiplication

#### Hadamard Matrix

- ***Reference***
```c
int Mat2Hadamard(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut);
int Mat3Hadamard(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);
int Mat4Hadamard(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);
```

- ***Parameters***
    - `mat1`: First Matrix Operand
    - `mat2`: Second Matrix Operand
    - `mOut`: A new matrix that is the result of Hadamard Product

- ***Return Value***
    - `int`: Error code

- ***Example***
```c
nml_t arr1[9] = {1.0, 4.0, 7.0,
                 2.0, 5.0, 8.0,
                 3.0, 6.0, 9.0};
nml_t arr2[9] = {9.0, 6.0, 3.0,
                 8.0, 5.0, 2.0,
                 7.0, 4.0, 1.0};
nml_t expected[9] = {9.0, 24.0, 21.0,
                     16.0, 25.0, 16.0,
                     21.0, 24.0, 9.0};
Mat mat2, mat2, result;
Mat2Init(arr, &A);
Mat2Init(arr, &B);
Mat2Hadamard(&A, &B, &result);
```

- ***Representation***
```math
\text{mat1}\odot\text{mat2}=\text{result}
```
```math
\begin{bmatrix}
1.0 & 4.0 & 7.0 \\
2.0 & 5.0 & 8.0 \\
3.0 & 6.0 & 9.0
\end{bmatrix} \quad
\odot \quad
\begin{bmatrix}
9.0 & 6.0 & 3.0 \\
8.0 & 5.0 & 2.0 \\
7.0 & 4.0 & 1.0
\end{bmatrix} \quad
\text{=} \quad
\begin{bmatrix}
9.0 & 24.0 & 21.0 \\
16.0 & 25.0 & 16.0 \\
21.0 & 24.0 & 9.0
\end{bmatrix} \quad
```

#### Matrix-Vector Multiplication

- ***Reference***
```c
int Mat2MulMat2(Mat2 *mat, Vec2 *vec, Vec2 *vOut);
int Mat3MulMat3(Mat3 *mat, Vec3 *vec, Vec3 *vOut);
int Mat4MulMat4(Mat4 *mat, Vec4 *vec, Vec4 *vOut);
```

- ***Parameters***
    - `mat` : Matrix Operand
    - `vec` : Vector Operand
    - `vOut`: A new vector that is the result of Matrix-Vector Multiplication

- ***Return Value***
    - `int`: Error code

- ***Example***
```c
nml_t mat_arr[9] = {1.0, 4.0, 7.0,
                    2.0, 5.0, 8.0,
                    3.0, 6.0, 9.0};

Mat3 mat;
Vec3 vec, result;
Mat3Init(mat_arr, &mat);
Vec3Init(2.0, 3.0, 4.0, &vec);
Mat3MulVec3(&mat, &vec, &result);
```

- ***Representation***
```math
\text{mat}\cdot\text{vec}=\text{result}
```
```math
\begin{bmatrix}
1.0 & 4.0 & 7.0 \\
2.0 & 5.0 & 8.0 \\
3.0 & 6.0 & 9.0
\end{bmatrix} \quad
\text{x} \quad
\begin{pmatrix}
2.0 \\
3 0 \\
4.0 \\
\end{pmatrix} \quad
\text{=} \quad
\begin{pmatrix}
20.0 \\
47.0 \\
74.0
\end{pmatrix} \quad
```

#### Matrix-Matrix Multiplication

- ***Reference***
```c
int Mat2MulMat2(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut);
int Mat3MulMat3(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);
int Mat4MulMat4(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);
```

- ***Parameters***
    - `mat1`: First Matrix Operand
    - `mat2`: Second Matrix Operand
    - `mOut`: A new matrix that is the result of Matrix-Matrix Multiplication

- ***Return Value***
    - `int`: Error code

- ***Example***
```c
nml_t arr1[4] = {1.0, 3.0,
                 2.0, 4.0};
nml_t arr2[4] = {4.0, 2.0,
                 3.0, 1.0};
Mat mat1, mat2, result;
Mat2Init(arr, &mat1);
Mat2Init(arr, &mat2);
Mat2Hadamard(&mat1, &mat2, &result);
```

- ***Representation***
```math
\text{mat}\cdot\text{vec}=\text{result}
```
```math
\begin{bmatrix}
1.0 & 3.0 \\
2.0 & 4.0
\end{bmatrix} \quad
\text{+} \quad
\begin{bmatrix}
4.0 & 2.0 \\
3.0 & 1.0
\end{bmatrix} \quad
\text{=} \quad
\begin{bmatrix}
8.0 & 20.0 \\
5.0 & 13.0
\end{bmatrix} \quad
```
