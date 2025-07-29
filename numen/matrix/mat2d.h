#ifndef __MAT2D_H__
#define __MAT2D_H__

#include "utils/consts.h"
#include "vector/vec2d.h"

typedef union Mat2 {
    nml_t Elements[4];
    Vec2 *Columns[2];
} Mat2;

// initialize a matrix from a 2d array (row-major)
int Mat2Init(const nml_t arr[4], Mat2 *mOut);
// initialize a matrix with all the elements set to 0.0f
int Mat2InitZero(Mat2 *mOut);
// initialize a diagonal matrix
int Mat2Diagonal(nml_t val, Mat2 *mOut);
// initialize a identity matrix
int Mat2Identity(Mat2 *mOut);

int Mat2Add(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut);
// subtract mat2 form mat1
int Mat2Sub(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut);
// hadamard's multiplication
int Mat2Hadamard(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut);

int Mat2Scale(Mat2 *mat, nml_t s, Mat2 *mOut);
int Mat2Negate(Mat2 *mat, Mat2 *mOut);

#endif // !__MAT2D_H__
