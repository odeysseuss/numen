## Initialization Functions

#### Initialize from a 2d Array (Column-Major)
- ***Reference***
```c
int Mat2Init(const nml_t arr[4], Mat2 *mOut);
int Mat3Init(const nml_t arr[9], Mat3 *mOut);
int Mat4Init(const nml_t arr[16], Mat4 *mOut);
```

- ***Parameters***
    - `arr`: 2d array of (float/double)s
        - For `Mat2: arr[4]`
        - For `Mat3: arr[9]`
        - For `Mat4: arr[16]`
    - `mOut`: Output pointer

- ***Return Value***
    - *A matrix populated with the values of the initial array*

- ***Example***
```c
nml_t array[4] = { 1.0, 3,0
                   2.0, 4.0 };
Mat2 A;
Mat2Init(array, &A);
```

- ***Representation***
```math
\text{A} = \begin{bmatrix}
1.0 & 2.0 \\
3.0 & 4.0
\end{bmatrix}
```

#### Initialize a Zero matrix
- ***Reference***
```c
int Mat2InitZero(Mat2 *mOut);
int Mat3InitZero(Mat3 *mOut);
int Mat4InitZero(Mat4 *mOut);
```

- ***Parameters***
    - `mOut`: Output pointer

- ***Return Value***
    - *A zero initialized matrix*

- ***Example***
```c
Mat3 A;
Mat2InitZero(Mat3 *mOut);
```

- ***Representation***
```math
\text{A} = \begin{bmatrix}
0 & 0 & 0 \\
0 & 0 & 0 \\
0 & 0 & 0
\end{bmatrix}
```

#### Initialize a Diagonal Matrix
- ***Reference***
```c
int Mat2Diagonal(nml_t val, Mat2 *mOut);
int Mat3Diagonal(nml_t val, Mat3 *mOut);
int Mat4Diagonal(nml_t val, Mat4 *mOut);
```

- ***Parameters***
    - `val`: Value to assign to the diagonal elements
    - `mOut`: Output pointer

- ***Return Value***
    - *A diagonal matrix with diagonal elements set to `val`*

- ***Example***
```c
Mat4 A;
Mat4Diagonal(5.0, &A);
```

- ***Representation***
```math
\text{A} = \begin{bmatrix}
5.0 & 0 & 0 & 0 \\
0 & 5.0 & 0 & 0 \\
0 & 0 & 5.0 & 0 \\
0 & 0 & 0 & 5.0
\end{bmatrix}
```

#### Initialize a Identity Matrix
- ***Reference***
```c
int Mat2Identity(Mat2 *mOut);
int Mat3Identity(Mat3 *mOut);
int Mat4Identity(Mat4 *mOut);
```

- ***Parameters***
    - `mOut`: Output pointer

- ***Return Value***
    - *A identity matrix*

- ***Example***
```c
Mat2 A;
Mat2Identity(&A);
```

- ***Representation***
```math
\text{A} = \begin{bmatrix}
1 & 0 \\
0 & 1
\end{bmatrix}
```
