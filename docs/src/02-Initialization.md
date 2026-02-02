## Initialization Functions

#### Initialize from a 2d Array (Column-Major)
- ***Reference***
```c
int mat2Init(const nml_t arr[4], Mat2 *mOut);
int mat3Init(const nml_t arr[9], Mat3 *mOut);
int mat4Init(const nml_t arr[16], Mat4 *mOut);
```

- ***Parameters***
    - `arr`: 2d array of (float/double)s
        - For `Mat2: arr[4]`
        - For `Mat3: arr[9]`
        - For `Mat4: arr[16]`
    - `mOut`: A matrix populated with the values of the initial array

- ***Return Value***
    - `int`: Error code

- ***Example***
```c
nml_t array[4] = { 1.0, 3,0
                   2.0, 4.0 };
Mat2 A;
mat2Init(array, &A);
```

- ***Representation***
\\[
\text{A} = \begin{bmatrix}
1.0 & 2.0 \\
3.0 & 4.0
\end{bmatrix}
\\]

#### Initialize a Zero matrix
- ***Reference***
```c
int mat2InitZero(Mat2 *mOut);
int mat3InitZero(Mat3 *mOut);
int mat4InitZero(Mat4 *mOut);
```

- ***Parameters***
    - `mOut`: A zero initialized matrix

- ***Return Value***
    - `int`: Error code

- ***Example***
```c
Mat3 A;
mat2InitZero(Mat3 *mOut);
```

- ***Representation***
\\[
\text{A} = \begin{bmatrix}
0 & 0 & 0 \\
0 & 0 & 0 \\
0 & 0 & 0
\end{bmatrix}
\\]

#### Initialize a Diagonal Matrix
- ***Reference***
```c
int mat2Diagonal(nml_t val, Mat2 *mOut);
int mat3Diagonal(nml_t val, Mat3 *mOut);
int mat4Diagonal(nml_t val, Mat4 *mOut);
```

- ***Parameters***
    - `val` : Value to assign to the diagonal elements
    - `mOut`: A diagonal matrix with diagonal elements set to `val`

- ***Return Value***
    - `int`: Error code

- ***Example***
```c
Mat4 A;
mat4Diagonal(5.0, &A);
```

- ***Representation***
\\[
\text{A} = \begin{bmatrix}
5.0 & 0 & 0 & 0 \\
0 & 5.0 & 0 & 0 \\
0 & 0 & 5.0 & 0 \\
0 & 0 & 0 & 5.0
\end{bmatrix}
\\]

#### Initialize a Identity Matrix
- ***Reference***
```c
int mat2Identity(Mat2 *mOut);
int mat3Identity(Mat3 *mOut);
int mat4Identity(Mat4 *mOut);
```

- ***Parameters***
    - `mOut`: A identity matrix

- ***Return Value***
    - `int`: Error code

- ***Example***
```c
Mat2 A;
mat2Identity(&A);
```

- ***Representation***
\\[
\text{A} = \begin{bmatrix}
1 & 0 \\
0 & 1
\end{bmatrix}
\\]
