## Basic Matrix Operations

#### Matrix Addition
- ***Reference***
```c
int Mat2Add(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut);
int Mat3Add(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);
int Mat4Add(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);
```

- ***Parameters***
    - `mat1`: First matrix operand
    - `mat2`: Second matrix operand
    - `mOut`: Output pointer

- ***Return Value***
    - *A new matrix that is the result of element-wise addition of mat1 and mat2*

- ***Example***
```c
Mat2 mat1, mat2, result;
Mat2Identity(&mat1);
Mat2Diagonal(2.0, &mat2);
Mat2Add(&mat1, &mat2, &result);
```

- ***Representation***
```math
\text{mat1}+\text{mat2}=\text{result}
```
```math
\begin{bmatrix}
1 & 0 \\
0 & 1
\end{bmatrix} \quad
\text{+} \quad
\begin{bmatrix}
2 & 0 \\
0 & 2
\end{bmatrix} \quad
\text{=} \quad
\begin{bmatrix}
3 & 0 \\
0 & 3
\end{bmatrix}
```

#### Matrix Subtraction
- ***Reference***
```c
int Mat2Sub(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut);
int Mat3Sub(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);
int Mat4Sub(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);
```

- ***Parameters***
    - `mat1`: First matrix operand (minuend)
    - `mat2`: Second matrix operand (subtrahend)
    - `mOut`: Output pointer

- ***Return Value***
    - *A new matrix that is the result of element-wise subtraction of mat2 from mat1*

- ***Example***
```c
Mat3 mat1, mat2, result;
Mat3Diagonal(5.0, &mat1);
Mat3Identity(&mat2);
Mat3Sub(&mat1, &mat2, &result);
```

- ***Representation***
```math
\text{mat1}-\text{mat2}=\text{result}
```
```math
\begin{bmatrix}
5 & 0 & 0 \\
0 & 5 & 0 \\
0 & 0 & 5
\end{bmatrix} \quad
\text{-} \quad
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{bmatrix} \quad
\text{=} \quad
\begin{bmatrix}
4 & 0 & 0 \\
0 & 4 & 0 \\
0 & 0 & 4
\end{bmatrix}
```

#### Matrix Scaling
- ***Reference***
```c
int Mat2Scale(Mat2 *mat, nml_t s, Mat2 *mOut);
int Mat3Scale(Mat3 *mat, nml_t s, Mat3 *mOut);
int Mat4Scale(Mat4 *mat, nml_t s, Mat4 *mOut);
```

- ***Parameters***
    - `mat`: Matrix to be scaled
    - `s`: Scalar value
    - `mOut`: Output pointer

- ***Return Value***
    - *A new matrix with all elements of mat multiplied by scalar s*

- ***Example***
```c
Mat4 mat, scaled;
Mat4Identity(&mat);
Mat4Scale(mat, 3.0, &scaled);
```

- ***Representation***
```math
\text{s}\cdot\text{mat}=\text{result}
```
```math
\text{3.0} \quad \cdot \quad
\begin{bmatrix}
1 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 \\
0 & 0 & 1 & 0 \\
0 & 0 & 0 & 1
\end{bmatrix} \quad
\text{=} \quad
\begin{bmatrix}
3 & 0 & 0 & 0 \\
0 & 3 & 0 & 0 \\
0 & 0 & 3 & 0 \\
0 & 0 & 0 & 3
\end{bmatrix}
```

#### Matrix negation

- ***Reference***
```c
int Mat2Negate(Mat2 *mat, Mat2 *mOut);
int Mat3Negate(Mat3 *mat, Mat3 *mOut);
int Mat4Negate(Mat4 *mat, Mat4 *mOut);
```

- ***Parameters***
    - `mat`: Matrix to negate
    - `mOut`: Output pointer

- ***Return Value***
    - *A new matrix with the elements negated*

- ***Example***
```c
nml_t arr[4] = { 1, 3, 2, 4 };
Mat2 mat, result;
Mat2Init(arr, &mat);
Mat2Negate(&mat, &result);
```

- ***Representation***
```math
\text{-} \text{mat} \quad = \quad \text{result}
```
```math
\text{-}
\begin{bmatrix}
1 & 2 \\
3 & 4
\end{bmatrix} \quad
\text{=} \quad
\begin{bmatrix}
-1 & -2 \\
-3 & -4
\end{bmatrix} \quad
```
