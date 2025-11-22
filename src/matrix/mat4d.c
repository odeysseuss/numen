#include "matrix/mat4d.h"
#include "utils/errors.h"
#include "utils/simd.h"
#include <string.h>

int mat4Init(const nml_t arr[16], Mat4 *mOut) {
    is_null(mOut);
    memcpy(mOut->elems, arr, sizeof(nml_t) * 16);
    return NML_SUCCESS;
}

int mat4InitZero(Mat4 *mOut) {
    is_null(mOut);
    memset(mOut, 0, sizeof(Mat4));
    return NML_SUCCESS;
}

int mat4Diagonal(nml_t val, Mat4 *mOut) {
    is_null(mOut);
    memset(mOut->elems, 0, sizeof(Mat4));
    for (int i = 0; i < 4; i++) {
        mOut->elems[i * 4 + i] = val;
    }
    return NML_SUCCESS;
}

int mat4Identity(Mat4 *mOut) {
    is_null(mOut);
    memset(mOut->elems, 0, sizeof(Mat4));
    for (int i = 0; i < 4; i++) {
        mOut->elems[i * 4 + i] = 1.0;
    }
    return NML_SUCCESS;
}

int mat4Add(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    is_null(mat1, mat2, mOut);

    simd_f32x4_t col0 = simd_add_f32(simd_load_f32(&mat1->elems[0]),
                                     simd_load_f32(&mat2->elems[0]));
    simd_f32x4_t col1 = simd_add_f32(simd_load_f32(&mat1->elems[4]),
                                     simd_load_f32(&mat2->elems[4]));
    simd_f32x4_t col2 = simd_add_f32(simd_load_f32(&mat1->elems[8]),
                                     simd_load_f32(&mat2->elems[8]));
    simd_f32x4_t col3 = simd_add_f32(simd_load_f32(&mat1->elems[12]),
                                     simd_load_f32(&mat2->elems[12]));

    simd_store_f32(&mOut->elems[0], col0);
    simd_store_f32(&mOut->elems[4], col1);
    simd_store_f32(&mOut->elems[8], col2);
    simd_store_f32(&mOut->elems[12], col3);

    return NML_SUCCESS;
}

int mat4Sub(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    is_null(mat1, mat2, mOut);

    simd_f32x4_t col0 = simd_sub_f32(simd_load_f32(&mat1->elems[0]),
                                     simd_load_f32(&mat2->elems[0]));
    simd_f32x4_t col1 = simd_sub_f32(simd_load_f32(&mat1->elems[4]),
                                     simd_load_f32(&mat2->elems[4]));
    simd_f32x4_t col2 = simd_sub_f32(simd_load_f32(&mat1->elems[8]),
                                     simd_load_f32(&mat2->elems[8]));
    simd_f32x4_t col3 = simd_sub_f32(simd_load_f32(&mat1->elems[12]),
                                     simd_load_f32(&mat2->elems[12]));

    simd_store_f32(&mOut->elems[0], col0);
    simd_store_f32(&mOut->elems[4], col1);
    simd_store_f32(&mOut->elems[8], col2);
    simd_store_f32(&mOut->elems[12], col3);

    return NML_SUCCESS;
}

int mat4Scale(Mat4 *mat, nml_t s, Mat4 *mOut) {
    is_null(mat, mOut);

    simd_f32x4_t scaler = simd_set1_f32(s);

    simd_f32x4_t col0 = simd_mul_f32(simd_load_f32(&mat->elems[0]), scaler);
    simd_f32x4_t col1 = simd_mul_f32(simd_load_f32(&mat->elems[4]), scaler);
    simd_f32x4_t col2 = simd_mul_f32(simd_load_f32(&mat->elems[8]), scaler);
    simd_f32x4_t col3 = simd_mul_f32(simd_load_f32(&mat->elems[12]), scaler);

    simd_store_f32(&mOut->elems[0], col0);
    simd_store_f32(&mOut->elems[4], col1);
    simd_store_f32(&mOut->elems[8], col2);
    simd_store_f32(&mOut->elems[12], col3);

    return NML_SUCCESS;
}

int mat4Negate(Mat4 *mat, Mat4 *mOut) {
    is_null(mat, mOut);

    simd_f32x4_t col0 = simd_negate_f32(simd_load_f32(&mat->elems[0]));
    simd_f32x4_t col1 = simd_negate_f32(simd_load_f32(&mat->elems[4]));
    simd_f32x4_t col2 = simd_negate_f32(simd_load_f32(&mat->elems[8]));
    simd_f32x4_t col3 = simd_negate_f32(simd_load_f32(&mat->elems[12]));

    simd_store_f32(&mOut->elems[0], col0);
    simd_store_f32(&mOut->elems[4], col1);
    simd_store_f32(&mOut->elems[8], col2);
    simd_store_f32(&mOut->elems[12], col3);

    return NML_SUCCESS;
}

int mat4Hadamard(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    is_null(mat1, mat2, mOut);

    simd_f32x4_t col0 = simd_mul_f32(simd_load_f32(&mat1->elems[0]),
                                     simd_load_f32(&mat2->elems[0]));
    simd_f32x4_t col1 = simd_mul_f32(simd_load_f32(&mat1->elems[4]),
                                     simd_load_f32(&mat2->elems[4]));
    simd_f32x4_t col2 = simd_mul_f32(simd_load_f32(&mat1->elems[8]),
                                     simd_load_f32(&mat2->elems[8]));
    simd_f32x4_t col3 = simd_mul_f32(simd_load_f32(&mat1->elems[12]),
                                     simd_load_f32(&mat2->elems[12]));

    simd_store_f32(&mOut->elems[0], col0);
    simd_store_f32(&mOut->elems[4], col1);
    simd_store_f32(&mOut->elems[8], col2);
    simd_store_f32(&mOut->elems[12], col3);

    return NML_SUCCESS;
}

int mat4MulVec4(Mat4 *mat, Vec4 *vec, Vec4 *vOut) {
    is_null(mat, vec, vOut);

#if defined(DEFINE_SIMD__SSE)
    simd_f32x4_t v = simd_load_f32(vec->elems);

    simd_f32x4_t res =
        simd_mul_f32(simd_load_f32(mat->cols[0].elems),
                     simd_shuffle_f32(v, SIMD_SHUFFLE(0, 0, 0, 0)));
    res = simd_add_f32(
        res,
        simd_mul_f32(simd_load_f32(mat->cols[1].elems),
                     simd_shuffle_f32(v, SIMD_SHUFFLE(1, 1, 1, 1))));
    res = simd_add_f32(
        res,
        simd_mul_f32(simd_load_f32(mat->cols[2].elems),
                     simd_shuffle_f32(v, SIMD_SHUFFLE(2, 2, 2, 2))));
    res = simd_add_f32(
        res,
        simd_mul_f32(simd_load_f32(mat->cols[3].elems),
                     simd_shuffle_f32(v, SIMD_SHUFFLE(3, 3, 3, 3))));

    simd_store_f32(vOut->elems, res);

#elif defined(DEFINE_SIMD__NEON)
    simd_f32x4_t v = simd_load_f32(vec->elems);

    float32x4_t res = simd_mul_lane_f32(
        simd_load_f32(mat->cols[0].elems), simd_get_low_f32(v), 0);
    res = simd_mla_lane_f32(
        res, simd_load_f32(mat->cols[1].elems), simd_get_low_f32(v), 1);
    res = simd_mla_lane_f32(
        res, simd_load_f32(mat->cols[2].elems), simd_get_high_f32(v), 0);
    res = simd_mla_lane_f32(
        res, simd_load_f32(mat->cols[3].elems), simd_get_high_f32(v), 1);

    simd_store_f32(vOut->elems, res);

#else
    vOut->x = vec->elems[0] * mat->cols[0].x + vec->elems[1] * mat->cols[1].x +
              vec->elems[2] * mat->cols[2].x + vec->elems[3] * mat->cols[3].x;
    vOut->y = vec->elems[0] * mat->cols[0].y + vec->elems[1] * mat->cols[1].y +
              vec->elems[2] * mat->cols[2].y + vec->elems[3] * mat->cols[3].y;
    vOut->z = vec->elems[0] * mat->cols[0].z + vec->elems[1] * mat->cols[1].z +
              vec->elems[2] * mat->cols[2].z + vec->elems[3] * mat->cols[3].z;
    vOut->w = vec->elems[0] * mat->cols[0].w + vec->elems[1] * mat->cols[1].w +
              vec->elems[2] * mat->cols[2].w + vec->elems[3] * mat->cols[3].w;
#endif

    return NML_SUCCESS;
}

int mat4MulMat4(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    is_null(mat1, mat2, mOut);

#if defined(DEFINE_SIMD__SSE)
    simd_f32x4_t mat1_col0 = simd_load_f32(&mat1->cols[0].x);
    simd_f32x4_t mat1_col1 = simd_load_f32(&mat1->cols[1].x);
    simd_f32x4_t mat1_col2 = simd_load_f32(&mat1->cols[2].x);
    simd_f32x4_t mat1_col3 = simd_load_f32(&mat1->cols[3].x);

    for (int i = 0; i < 4; i++) {
        simd_f32x4_t mat2_col = simd_load_f32(&mat2->cols[i].x);

        simd_f32x4_t bc0 = simd_set1_f32(simd_extract0_f32(mat2_col));
        simd_f32x4_t bc1 = simd_set1_f32(simd_extract1_f32(mat2_col));
        simd_f32x4_t bc2 = simd_set1_f32(simd_extract2_f32(mat2_col));
        simd_f32x4_t bc3 = simd_set1_f32(simd_extract3_f32(mat2_col));

        simd_f32x4_t result = simd_mul_f32(mat1_col0, bc0);
        result = simd_add_f32(result, simd_mul_f32(mat1_col1, bc1));
        result = simd_add_f32(result, simd_mul_f32(mat1_col2, bc2));
        result = simd_add_f32(result, simd_mul_f32(mat1_col3, bc3));

        simd_store_f32(&mOut->cols[i].x, result);
    }

#elif defined(DEFINE_SIMD__NEON)
    simd_f32x4_t mat1_col0 = simd_load_f32(&mat1->cols[0].x);
    simd_f32x4_t mat1_col1 = simd_load_f32(&mat1->cols[1].x);
    simd_f32x4_t mat1_col2 = simd_load_f32(&mat1->cols[2].x);
    simd_f32x4_t mat1_col3 = simd_load_f32(&mat1->cols[3].x);

    for (int i = 0; i < 4; i++) {
        simd_f32x4_t mat2_col = simd_load_f32(&mat2->cols[i].x);

        simd_f32x4_t bc0 = simd_dup_lane_f32(mat2_col, 0);
        simd_f32x4_t bc1 = simd_dup_lane_f32(mat2_col, 1);
        simd_f32x4_t bc2 = simd_dup_lane_f32(mat2_col, 2);
        simd_f32x4_t bc3 = simd_dup_lane_f32(mat2_col, 3);

        simd_f32x4_t result = simd_mul_f32(mat1_col0, bc0);
        result = simd_fmadd_f32(mat1_col1, bc1, result);
        result = simd_fmadd_f32(mat1_col2, bc2, result);
        result = simd_fmadd_f32(mat1_col3, bc3, result);

        simd_store_f32(&mOut->cols[i].x, result);
    }

#else
    mat4MulVec4(mat1, &mat2->cols[0], &mOut->cols[0]);
    mat4MulVec4(mat1, &mat2->cols[1], &mOut->cols[1]);
    mat4MulVec4(mat1, &mat2->cols[2], &mOut->cols[2]);
    mat4MulVec4(mat1, &mat2->cols[3], &mOut->cols[3]);
#endif

    return NML_SUCCESS;
}
