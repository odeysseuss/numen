#include "matrix/mat3d.h"
#include "utils/errors.h"
#include <string.h>

int Mat3Init(const nml_t arr[9], Mat3 *mOut) {
    NULL_POINTERS(mOut);
    memcpy(mOut->Elements, arr, sizeof(nml_t) * 9);
    return NML_SUCCESS;
}

int Mat3InitZero(Mat3 *mOut) {
    NULL_POINTERS(mOut);
    memset(mOut, 0, sizeof(Mat3));
    return NML_SUCCESS;
}

int Mat3Diagonal(nml_t val, Mat3 *mOut) {
    NULL_POINTERS(mOut);
    memset(mOut->Elements, 0, sizeof(Mat3));
    for (int i = 0; i < 3; i++) {
        mOut->Elements[i * 3 + i] = val;
    }

    return NML_SUCCESS;
}

int Mat3Identity(Mat3 *mOut) {
    NULL_POINTERS(mOut);
    memset(mOut->Elements, 0, sizeof(Mat3));
    for (int i = 0; i < 3; i++) {
        mOut->Elements[i * 3 + i] = 1.0;
    }

    return NML_SUCCESS;
}

int Mat3Add(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
    for (int i = 0; i < 9; i++) {
        mOut->Elements[i] = mat1->Elements[i] + mat2->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat3Sub(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
    for (int i = 0; i < 9; i++) {
        mOut->Elements[i] = mat1->Elements[i] - mat2->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat3Hadamard(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
    for (int i = 0; i < 9; i++) {
        mOut->Elements[i] = mat1->Elements[i] * mat2->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat3Scale(Mat3 *mat, nml_t s, Mat3 *mOut) {
    NULL_POINTERS(mat, mOut);
    for (int i = 0; i < 9; i++) {
        mOut->Elements[i] = mat->Elements[i] * s;
    }

    return NML_SUCCESS;
}

int Mat3Negate(Mat3 *mat, Mat3 *mOut) {
    NULL_POINTERS(mat, mOut);
    for (int i = 0; i < 9; i++) {
        mOut->Elements[i] = -mat->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat3MulVec3(Mat3 *mat, Vec3 *vec, Vec3 *vOut) {
    NULL_POINTERS(mat, vec, vOut);
    vOut->X = mat->Columns[0].X * vec->X + mat->Columns[1].X * vec->Y +
              mat->Columns[2].X * vec->Z;
    vOut->Y = mat->Columns[0].Y * vec->X + mat->Columns[1].Y * vec->Y +
              mat->Columns[2].Y * vec->Z;
    vOut->Z = mat->Columns[0].Z * vec->X + mat->Columns[1].Z * vec->Y +
              mat->Columns[2].Z * vec->Z;

    return NML_SUCCESS;
}

int Mat3MulMat3(Mat3 *mat1, Mat3 *mat2, Mat3 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
    Mat3MulVec3(mat1, &mat2->Columns[0], &mOut->Columns[0]);
    Mat3MulVec3(mat1, &mat2->Columns[1], &mOut->Columns[1]);
    Mat3MulVec3(mat1, &mat2->Columns[2], &mOut->Columns[2]);

    return NML_SUCCESS;
}
