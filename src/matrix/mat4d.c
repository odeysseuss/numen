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
