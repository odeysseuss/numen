#ifndef __MAT3D_H__
#define __MAT3D_H__

#include "utils/consts.h"
#include "vector/vec3d.h"

typedef union Mat3 {
    nml_t elems[9];
    Vec3 cols[3];
} Mat3;

int mat3Init(const nml_t arr[9], Mat3 *mOut);
int mat3InitZero(Mat3 *mOut);
int mat3Diagonal(nml_t val, Mat3 *mOut);
int mat3Identity(Mat3 *mOut);

int mat3Add(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);
// subtract mat2 form mat1
int mat3Sub(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);

int mat3Scale(Mat3 *mat, nml_t s, Mat3 *mOut);
int mat3Negate(Mat3 *mat, Mat3 *mOut);

// matrix multiplication
int mat3Hadamard(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);
int mat3MulVec3(Mat3 *mat, Vec3 *vec, Vec3 *vOut);
int mat3MulMat3(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);

#endif // !__MAT3D_H__
