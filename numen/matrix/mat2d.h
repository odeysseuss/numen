#ifndef __MAT2D_H__
#define __MAT2D_H__

#include "utils/consts.h"
#include "vector/vec2d.h"

typedef union Mat2 {
    nml_t elems[4];
    Vec2 cols[2];
} Mat2;

int mat2Init(const nml_t arr[4], Mat2 *mOut);
int mat2InitZero(Mat2 *mOut);
// initialize a diagonal matrix
int mat2Diagonal(nml_t val, Mat2 *mOut);
// initialize a identity matrix
int mat2Identity(Mat2 *mOut);

int mat2Add(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut);
// subtract mat2 form mat1
int mat2Sub(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut);

int mat2Scale(Mat2 *mat, nml_t s, Mat2 *mOut);
int mat2Negate(Mat2 *mat, Mat2 *mOut);

// matrix multiplication
int mat2Hadamard(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut);
int mat2MulVec2(Mat2 *mat, Vec2 *vec, Vec2 *vOut);
int mat2MulMat2(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut);

#endif // !__MAT2D_H__
