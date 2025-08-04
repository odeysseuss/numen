#include "matrix/mat3d.h"
#include "utils/errors.h"
#include <string.h>

int Mat3Init(const nml_t arr[9], Mat3 *mOut) {
    memcpy(mOut->Elements, arr, sizeof(nml_t) * 9);
    return NML_SUCCESS;
}

int Mat3InitZero(Mat3 *mOut) {
    memset(mOut, 0, sizeof(Mat3));
    return NML_SUCCESS;
}

int Mat3Diagonal(nml_t val, Mat3 *mOut) {
    memset(mOut->Elements, 0, sizeof(Mat3));
    for (int i = 0; i < 3; i++) {
        mOut->Elements[i * 3 + i] = val;
    }

    return NML_SUCCESS;
}

int Mat3Identity(Mat3 *mOut) {
    memset(mOut->Elements, 0, sizeof(Mat3));
    for (int i = 0; i < 3; i++) {
        mOut->Elements[i * 3 + i] = 1.0;
    }

    return NML_SUCCESS;
}

int Mat3Add(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut) {
    for (int i = 0; i < 9; i++) {
        mOut->Elements[i] = mat1->Elements[i] + mat2->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat3Sub(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut) {
    for (int i = 0; i < 9; i++) {
        mOut->Elements[i] = mat1->Elements[i] - mat2->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat3Hadamard(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut) {
    for (int i = 0; i < 9; i++) {
        mOut->Elements[i] = mat1->Elements[i] * mat2->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat3Scale(Mat3 *mat, nml_t s, Mat3 *mOut) {
    for (int i = 0; i < 9; i++) {
        mOut->Elements[i] = mat->Elements[i] * s;
    }

    return NML_SUCCESS;
}

int Mat3Negate(Mat3 *mat, Mat3 *mOut) {
    for (int i = 0; i < 9; i++) {
        mOut->Elements[i] = -mat->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat3MulVec3(Mat3 *mat, Vec3 *vec, Vec3 *vOut) {
    vOut->x = mat->Columns[0].x * vec->x + mat->Columns[1].x * vec->y +
              mat->Columns[2].x * vec->z;
    vOut->y = mat->Columns[0].y * vec->x + mat->Columns[1].y * vec->y +
              mat->Columns[2].y * vec->z;
    vOut->z = mat->Columns[0].z * vec->x + mat->Columns[1].z * vec->y +
              mat->Columns[2].z * vec->z;

    return NML_SUCCESS;
}

int Mat3MulMat3(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut) {
    Mat3MulVec3(mat1, &mat2->Columns[0], &mOut->Columns[0]);
    Mat3MulVec3(mat1, &mat2->Columns[1], &mOut->Columns[1]);
    Mat3MulVec3(mat1, &mat2->Columns[2], &mOut->Columns[2]);

    return NML_SUCCESS;
}
