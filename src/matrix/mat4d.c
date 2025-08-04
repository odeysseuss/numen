#include "matrix/mat4d.h"
#include "utils/errors.h"
#include <string.h>

int Mat4Init(const nml_t arr[16], Mat4 *mOut) {
    memcpy(mOut->Elements, arr, sizeof(nml_t) * 16);
    return NML_SUCCESS;
}

int Mat4InitZero(Mat4 *mOut) {
    memset(mOut, 0, sizeof(Mat4));
    return NML_SUCCESS;
}

int Mat4Diagonal(nml_t val, Mat4 *mOut) {
    memset(mOut->Elements, 0, sizeof(Mat4));
    for (int i = 0; i < 4; i++) {
        mOut->Elements[i * 4 + i] = val;
    }

    return NML_SUCCESS;
}

int Mat4Identity(Mat4 *mOut) {
    memset(mOut->Elements, 0, sizeof(Mat4));
    for (int i = 0; i < 4; i++) {
        mOut->Elements[i * 4 + i] = 1.0;
    }

    return NML_SUCCESS;
}

int Mat4Add(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    for (int i = 0; i < 16; i++) {
        mOut->Elements[i] = mat1->Elements[i] + mat2->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat4Sub(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    for (int i = 0; i < 16; i++) {
        mOut->Elements[i] = mat1->Elements[i] - mat2->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat4Hadamard(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    for (int i = 0; i < 16; i++) {
        mOut->Elements[i] = mat1->Elements[i] * mat2->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat4Scale(Mat4 *mat, nml_t s, Mat4 *mOut) {
    for (int i = 0; i < 16; i++) {
        mOut->Elements[i] = mat->Elements[i] * s;
    }

    return NML_SUCCESS;
}

int Mat4Negate(Mat4 *mat, Mat4 *mOut) {
    for (int i = 0; i < 16; i++) {
        mOut->Elements[i] = -mat->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat4MulVec4(Mat4 *mat, Vec4 *vec, Vec4 *vOut) {
    vOut->x = vec->Elements[0] * mat->Columns[0].x +
              vec->Elements[1] * mat->Columns[1].x +
              vec->Elements[2] * mat->Columns[2].x +
              vec->Elements[3] * mat->Columns[3].x;
    vOut->y = vec->Elements[0] * mat->Columns[0].y +
              vec->Elements[1] * mat->Columns[1].y +
              vec->Elements[2] * mat->Columns[2].y +
              vec->Elements[3] * mat->Columns[3].y;
    vOut->z = vec->Elements[0] * mat->Columns[0].z +
              vec->Elements[1] * mat->Columns[1].z +
              vec->Elements[2] * mat->Columns[2].z +
              vec->Elements[3] * mat->Columns[3].z;

    vOut->w = vec->Elements[0] * mat->Columns[0].w +
              vec->Elements[1] * mat->Columns[1].w +
              vec->Elements[2] * mat->Columns[2].w +
              vec->Elements[3] * mat->Columns[3].w;

    return NML_SUCCESS;
}

int Mat4MulMat4(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    Mat4MulVec4(mat1, &mat2->Columns[0], &mOut->Columns[0]);
    Mat4MulVec4(mat1, &mat2->Columns[1], &mOut->Columns[1]);
    Mat4MulVec4(mat1, &mat2->Columns[2], &mOut->Columns[2]);
    Mat4MulVec4(mat1, &mat2->Columns[3], &mOut->Columns[3]);

    return NML_SUCCESS;
}
