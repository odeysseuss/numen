#ifndef __MAT4D_H__
#define __MAT4D_H__

#include "utils/consts.h"
#include "utils/simd.h"
#include "vector/vec4d.h"

typedef union Mat4 {
    nml_t elems[16];
    Vec4 cols[4];
} Mat4 ALIGN_16;

int mat4Init(const nml_t arr[16], Mat4 *mOut);
int mat4InitZero(Mat4 *mOut);
int mat4Diagonal(nml_t val, Mat4 *mOut);
int mat4Identity(Mat4 *mOut);

int mat4Add(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);
// subtract mat2 form mat1
int mat4Sub(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);

int mat4Scale(Mat4 *mat, nml_t s, Mat4 *mOut);
int mat4Negate(Mat4 *mat, Mat4 *mOut);

// matrix multiplication
int mat4Hadamard(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);
int mat4MulVec4(Mat4 *mat, Vec4 *vec, Vec4 *vOut);
int mat4MulMat4(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut);

#endif // !__MAT4D_H__
