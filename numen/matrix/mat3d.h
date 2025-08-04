#ifndef __MAT3D_H__
#define __MAT3D_H__

#include "utils/consts.h"
#include "vector/vec3d.h"

typedef union Mat3 {
    nml_t Elements[9];
    Vec3 Columns[3];
} Mat3;

int Mat3Init(const nml_t arr[9], Mat3 *mOut);
int Mat3InitZero(Mat3 *mOut);
int Mat3Diagonal(nml_t val, Mat3 *mOut);
int Mat3Identity(Mat3 *mOut);

int Mat3Add(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);
// subtract mat2 form mat1
int Mat3Sub(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);

int Mat3Scale(Mat3 *mat, nml_t s, Mat3 *mOut);
int Mat3Negate(Mat3 *mat, Mat3 *mOut);

// matrix multiplication
int Mat3Hadamard(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);
int Mat3MulVec3(Mat3 *mat, Vec3 *vec, Vec3 *vOut);
int Mat3MulMat3(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut);

#endif // !__MAT3D_H__
