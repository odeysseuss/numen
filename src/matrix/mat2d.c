#include "matrix/mat2d.h"
#include "utils/errors.h"
#include <string.h>

int Mat2Init(const nml_t arr[4], Mat2 *mOut) {
    memcpy(mOut->Elements, arr, sizeof(nml_t) * 4);
    return NML_SUCCESS;
}

int Mat2InitZero(Mat2 *mOut) {
    memset(mOut, 0, sizeof(Mat2));
    return NML_SUCCESS;
}

int Mat2Diagonal(nml_t val, Mat2 *mOut) {
    memset(mOut->Elements, 0, sizeof(Mat2));
    for (int i = 0; i < 2; i++) {
        mOut->Elements[i * 2 + i] = val;
    }

    return NML_SUCCESS;
}

int Mat2Identity(Mat2 *mOut) {
    memset(mOut->Elements, 0, sizeof(Mat2));
    for (int i = 0; i < 2; i++) {
        mOut->Elements[i * 2 + i] = 1.0;
    }

    return NML_SUCCESS;
}

int Mat2Add(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut) {
    for (int i = 0; i < 4; i++) {
        mOut->Elements[i] = mat1->Elements[i] + mat2->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat2Sub(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut) {
    for (int i = 0; i < 4; i++) {
        mOut->Elements[i] = mat1->Elements[i] - mat2->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat2Hadamard(Mat2 *mat1, Mat2 *mat2, Mat2 *mOut) {
    for (int i = 0; i < 4; i++) {
        mOut->Elements[i] = mat1->Elements[i] * mat2->Elements[i];
    }

    return NML_SUCCESS;
}

int Mat2Scale(Mat2 *mat, nml_t s, Mat2 *mOut) {
    for (int i = 0; i < 4; i++) {
        mOut->Elements[i] = mat->Elements[i] * s;
    }

    return NML_SUCCESS;
}

int Mat2Negate(Mat2 *mat, Mat2 *mOut) {
    for (int i = 0; i < 4; i++) {
        mOut->Elements[i] = -mat->Elements[i];
    }

    return NML_SUCCESS;
}
