## Basic Matrix Operations

#### Matrix Addition
- ***Reference***
```c
int mat2Add(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut);
int mat3Add(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);
int mat4Add(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);
```

- ***Parameters***
    - `mat1`: First matrix operand
    - `mat2`: Second matrix operand
    - `mOut`: A new matrix that is the result of element-wise addition of mat1 and mat2

- ***Return Value***
    - `int`: Error code

- ***Example***
```c
Mat2 mat1, mat2, result;
mat2Identity(&mat1);
mat2Diagonal(2.0, &mat2);
mat2Add(&mat1, &mat2, &result);
```

- ***Representation***
\\[
\text{mat1}+\text{mat2}=\text{result}
\\]

\\[
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
\\]

#### Matrix Subtraction
- ***Reference***
```c
int mat2Sub(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut);
int mat3Sub(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);
int mat4Sub(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);
```

- ***Parameters***
    - `mat1`: First matrix operand (minuend)
    - `mat2`: Second matrix operand (subtrahend)
    - `mOut`: A new matrix that is the result of element-wise subtraction of mat2 from mat1

- ***Return Value***
    - `int`: Error code

- ***Example***
```c
Mat3 mat1, mat2, result;
mat3Diagonal(5.0, &mat1);
mat3Identity(&mat2);
mat3Sub(&mat1, &mat2, &result);
```

- ***Representation***
\\[
\text{mat1}-\text{mat2}=\text{result}
\\]

\\[
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
\\]

#### Matrix Scaling
- ***Reference***
```c
int mat2Scale(Mat2 *mat, nml_t s, Mat2 *mOut);
int mat3Scale(Mat3 *mat, nml_t s, Mat3 *mOut);
int mat4Scale(Mat4 *mat, nml_t s, Mat4 *mOut);
```

- ***Parameters***
    - `mat`: Matrix to be scaled
    - `s`: Scalar value
    - `mOut`: A new matrix with all elements of mat multiplied by scalar s

- ***Return Value***
    - `int`: Error code

- ***Example***
```c
Mat4 mat, scaled;
mat4Identity(&mat);
mat4Scale(mat, 3.0, &scaled);
```

- ***Representation***
\\[
\text{s}\cdot\text{mat}=\text{result}
\\]

\\[
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
\\]

#### Matrix negation

- ***Reference***
```c
int mat2Negate(Mat2 *mat, Mat2 *mOut);
int mat3Negate(Mat3 *mat, Mat3 *mOut);
int mat4Negate(Mat4 *mat, Mat4 *mOut);
```

- ***Parameters***
    - `mat`: Matrix to negate
    - `mOut`: A new matrix with the elements negated

- ***Return Value***
    - `int`: Error code

- ***Example***
```c
nml_t arr[4] = { 1, 3, 2, 4 };
Mat2 mat, result;
mat2Init(arr, &mat);
mat2Negate(&mat, &result);
```

- ***Representation***
\\[
\text{-} \text{mat} \quad = \quad \text{result}
\\]

\\[
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
\\]
