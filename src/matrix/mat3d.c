#include "matrix/mat3d.h"
#include "utils/errors.h"
#include <string.h>

int mat3Init(const nml_t arr[9], Mat3 *mOut) {
    NULL_POINTERS(mOut);
    memcpy(mOut->elems, arr, sizeof(nml_t) * 9);
    return NML_SUCCESS;
}

int mat3InitZero(Mat3 *mOut) {
    NULL_POINTERS(mOut);
    memset(mOut, 0, sizeof(Mat3));
    return NML_SUCCESS;
}

int mat3Diagonal(nml_t val, Mat3 *mOut) {
    NULL_POINTERS(mOut);
    memset(mOut->elems, 0, sizeof(Mat3));
    for (int i = 0; i < 3; i++) {
        mOut->elems[i * 3 + i] = val;
    }

    return NML_SUCCESS;
}

int mat3Identity(Mat3 *mOut) {
    NULL_POINTERS(mOut);
    memset(mOut->elems, 0, sizeof(Mat3));
    for (int i = 0; i < 3; i++) {
        mOut->elems[i * 3 + i] = 1.0;
    }

    return NML_SUCCESS;
}

int mat3Add(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
    for (int i = 0; i < 9; i++) {
        mOut->elems[i] = mat1->elems[i] + mat2->elems[i];
    }

    return NML_SUCCESS;
}

int mat3Sub(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
    for (int i = 0; i < 9; i++) {
        mOut->elems[i] = mat1->elems[i] - mat2->elems[i];
    }

    return NML_SUCCESS;
}

int mat3Hadamard(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
    for (int i = 0; i < 9; i++) {
        mOut->elems[i] = mat1->elems[i] * mat2->elems[i];
    }

    return NML_SUCCESS;
}

int mat3Scale(Mat3 *mat, nml_t s, Mat3 *mOut) {
    NULL_POINTERS(mat, mOut);
    for (int i = 0; i < 9; i++) {
        mOut->elems[i] = mat->elems[i] * s;
    }

    return NML_SUCCESS;
}

int mat3Negate(Mat3 *mat, Mat3 *mOut) {
    NULL_POINTERS(mat, mOut);
    for (int i = 0; i < 9; i++) {
        mOut->elems[i] = -mat->elems[i];
    }

    return NML_SUCCESS;
}

int mat3MulVec3(Mat3 *mat, Vec3 *vec, Vec3 *vOut) {
    NULL_POINTERS(mat, vec, vOut);
    vOut->x = mat->cols[0].x * vec->x + mat->cols[1].x * vec->y +
              mat->cols[2].x * vec->z;
    vOut->y = mat->cols[0].y * vec->x + mat->cols[1].y * vec->y +
              mat->cols[2].y * vec->z;
    vOut->z = mat->cols[0].z * vec->x + mat->cols[1].z * vec->y +
              mat->cols[2].z * vec->z;

    return NML_SUCCESS;
}

int mat3MulMat3(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
    mat3MulVec3(mat1, &mat2->cols[0], &mOut->cols[0]);
    mat3MulVec3(mat1, &mat2->cols[1], &mOut->cols[1]);
    mat3MulVec3(mat1, &mat2->cols[2], &mOut->cols[2]);

    return NML_SUCCESS;
}
