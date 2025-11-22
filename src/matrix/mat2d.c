#include "matrix/mat2d.h"
#include "utils/errors.h"
#include <string.h>

int mat2Init(const nml_t arr[4], Mat2 *mOut) {
    is_null(mOut);
    memcpy(mOut->elems, arr, sizeof(nml_t) * 4);
    return NML_SUCCESS;
}

int mat2InitZero(Mat2 *mOut) {
    is_null(mOut);
    memset(mOut, 0, sizeof(Mat2));
    return NML_SUCCESS;
}

int mat2Diagonal(nml_t val, Mat2 *mOut) {
    is_null(mOut);
    memset(mOut->elems, 0, sizeof(Mat2));
    for (int i = 0; i < 2; i++) {
        mOut->elems[i * 2 + i] = val;
    }

    return NML_SUCCESS;
}

int mat2Identity(Mat2 *mOut) {
    is_null(mOut);
    memset(mOut->elems, 0, sizeof(Mat2));
    for (int i = 0; i < 2; i++) {
        mOut->elems[i * 2 + i] = 1.0;
    }

    return NML_SUCCESS;
}

int mat2Add(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut) {
    is_null(mat1, mat2, mOut);
    for (int i = 0; i < 4; i++) {
        mOut->elems[i] = mat1->elems[i] + mat2->elems[i];
    }

    return NML_SUCCESS;
}

int mat2Sub(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut) {
    is_null(mat1, mat2, mOut);
    for (int i = 0; i < 4; i++) {
        mOut->elems[i] = mat1->elems[i] - mat2->elems[i];
    }

    return NML_SUCCESS;
}

int mat2Hadamard(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut) {
    is_null(mat1, mat2, mOut);
    for (int i = 0; i < 4; i++) {
        mOut->elems[i] = mat1->elems[i] * mat2->elems[i];
    }

    return NML_SUCCESS;
}

int mat2Scale(Mat2 *mat, nml_t s, Mat2 *mOut) {
    is_null(mat, mOut);
    for (int i = 0; i < 4; i++) {
        mOut->elems[i] = mat->elems[i] * s;
    }

    return NML_SUCCESS;
}

int mat2Negate(Mat2 *mat, Mat2 *mOut) {
    is_null(mat, mOut);
    for (int i = 0; i < 4; i++) {
        mOut->elems[i] = -mat->elems[i];
    }

    return NML_SUCCESS;
}

int mat2MulVec2(Mat2 *mat, Vec2 *vec, Vec2 *vOut) {
    is_null(mat, vec, vOut);
    vOut->x = vec->elems[0] * mat->cols[0].x +
              vec->elems[1] * mat->cols[1].x;
    vOut->y = vec->elems[0] * mat->cols[0].y +
              vec->elems[1] * mat->cols[1].y;

    return NML_SUCCESS;
}

int mat2MulMat2(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut) {
    is_null(mat1, mat2, mOut);
    mat2MulVec2(mat1, &mat2->cols[0], &mOut->cols[0]);
    mat2MulVec2(mat1, &mat2->cols[1], &mOut->cols[1]);

    return NML_SUCCESS;
}
