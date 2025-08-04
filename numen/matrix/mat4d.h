#ifndef __MAT4D_H__
#define __MAT4D_H__

#include "utils/consts.h"
#include "vector/vec4d.h"

typedef union Mat4 {
    nml_t Elements[16];
    Vec4 Columns[4];
} Mat4;

int Mat4Init(const nml_t arr[16], Mat4 *mOut);
int Mat4InitZero(Mat4 *mOut);
int Mat4Diagonal(nml_t val, Mat4 *mOut);
int Mat4Identity(Mat4 *mOut);

int Mat4Add(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);
// subtract mat2 form mat1
int Mat4Sub(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);

int Mat4Scale(Mat4 *mat, nml_t s, Mat4 *mOut);
int Mat4Negate(Mat4 *mat, Mat4 *mOut);

// matrix multiplication
int Mat4Hadamard(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);
int Mat4MulVec4(Mat4 *mat, Vec4 *vec, Vec4 *vOut);
int Mat4MulMat4(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);

#endif // !__MAT4D_H__
