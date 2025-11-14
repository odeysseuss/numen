#include "matrix/mat4d.h"
#include "utils/errors.h"
#include <string.h>

int mat4Init(const nml_t arr[16], Mat4 *mOut) {
    NULL_POINTERS(mOut);
    memcpy(mOut->elems, arr, sizeof(nml_t) * 16);
    return NML_SUCCESS;
}

int mat4InitZero(Mat4 *mOut) {
    NULL_POINTERS(mOut);
    memset(mOut, 0, sizeof(Mat4));
    return NML_SUCCESS;
}

int mat4Diagonal(nml_t val, Mat4 *mOut) {
    NULL_POINTERS(mOut);
    memset(mOut->elems, 0, sizeof(Mat4));
    for (int i = 0; i < 4; i++) {
        mOut->elems[i * 4 + i] = val;
    }

    return NML_SUCCESS;
}

int mat4Identity(Mat4 *mOut) {
    NULL_POINTERS(mOut);
    memset(mOut->elems, 0, sizeof(Mat4));
    for (int i = 0; i < 4; i++) {
        mOut->elems[i * 4 + i] = 1.0;
    }

    return NML_SUCCESS;
}

int mat4Add(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
#if defined(USE_SIMD__NEON)
    float32x4_t col0 =
        vaddq_f32(vld1q_f32(&mat1->elems[0]), vld1q_f32(&mat2->elems[0]));
    float32x4_t col1 =
        vaddq_f32(vld1q_f32(&mat1->elems[4]), vld1q_f32(&mat2->elems[4]));
    float32x4_t col2 =
        vaddq_f32(vld1q_f32(&mat1->elems[8]), vld1q_f32(&mat2->elems[8]));
    float32x4_t col3 = vaddq_f32(vld1q_f32(&mat1->elems[12]),
                                 vld1q_f32(&mat2->elems[12]));

    vst1q_f32(&mOut->elems[0], col0);
    vst1q_f32(&mOut->elems[4], col1);
    vst1q_f32(&mOut->elems[8], col2);
    vst1q_f32(&mOut->elems[12], col3);

    return NML_SUCCESS;

#elif defined(USE_SIMD__SSE)
    __m128 col0 = _mm_add_ps(_mm_load_ps(&mat1->elems[0]),
                             _mm_load_ps(&mat2->elems[0]));
    __m128 col1 = _mm_add_ps(_mm_load_ps(&mat1->elems[4]),
                             _mm_load_ps(&mat2->elems[4]));
    __m128 col2 = _mm_add_ps(_mm_load_ps(&mat1->elems[8]),
                             _mm_load_ps(&mat2->elems[8]));
    __m128 col3 = _mm_add_ps(_mm_load_ps(&mat1->elems[12]),
                             _mm_load_ps(&mat2->elems[12]));

    _mm_store_ps(&mOut->elems[0], col0);
    _mm_store_ps(&mOut->elems[4], col1);
    _mm_store_ps(&mOut->elems[8], col2);
    _mm_store_ps(&mOut->elems[12], col3);

    return NML_SUCCESS;

#else
    for (int i = 0; i < 16; i++) {
        mOut->elems[i] = mat1->elems[i] + mat2->elems[i];
    }

    return NML_SUCCESS;

#endif
}

int mat4Sub(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
#if defined(USE_SIMD__NEON)
    float32x4_t col0 =
        vsubq_f32(vld1q_f32(&mat1->elems[0]), vld1q_f32(&mat2->elems[0]));
    float32x4_t col1 =
        vsubq_f32(vld1q_f32(&mat1->elems[4]), vld1q_f32(&mat2->elems[4]));
    float32x4_t col2 =
        vsubq_f32(vld1q_f32(&mat1->elems[8]), vld1q_f32(&mat2->elems[8]));
    float32x4_t col3 = vsubq_f32(vld1q_f32(&mat1->elems[12]),
                                 vld1q_f32(&mat2->elems[12]));

    vst1q_f32(&mOut->elems[0], col0);
    vst1q_f32(&mOut->elems[4], col1);
    vst1q_f32(&mOut->elems[8], col2);
    vst1q_f32(&mOut->elems[12], col3);

    return NML_SUCCESS;

#elif defined(USE_SIMD__SSE)
    __m128 col0 = _mm_sub_ps(_mm_load_ps(&mat1->elems[0]),
                             _mm_load_ps(&mat2->elems[0]));
    __m128 col1 = _mm_sub_ps(_mm_load_ps(&mat1->elems[4]),
                             _mm_load_ps(&mat2->elems[4]));
    __m128 col2 = _mm_sub_ps(_mm_load_ps(&mat1->elems[8]),
                             _mm_load_ps(&mat2->elems[8]));
    __m128 col3 = _mm_sub_ps(_mm_load_ps(&mat1->elems[12]),
                             _mm_load_ps(&mat2->elems[12]));

    _mm_store_ps(&mOut->elems[0], col0);
    _mm_store_ps(&mOut->elems[4], col1);
    _mm_store_ps(&mOut->elems[8], col2);
    _mm_store_ps(&mOut->elems[12], col3);

    return NML_SUCCESS;

#else
    for (int i = 0; i < 16; i++) {
        mOut->elems[i] = mat1->elems[i] - mat2->elems[i];
    }

    return NML_SUCCESS;

#endif
}

int mat4Scale(Mat4 *mat, nml_t s, Mat4 *mOut) {
    NULL_POINTERS(mat, mOut);
#if defined(USE_SIMD__NEON)
    float32x4_t scaler = vdupq_n_f32(s);

    float32x4_t col0 = vmulq_f32(vld1q_f32(&mat->elems[0]), scaler);
    float32x4_t col1 = vmulq_f32(vld1q_f32(&mat->elems[4]), scaler);
    float32x4_t col2 = vmulq_f32(vld1q_f32(&mat->elems[8]), scaler);
    float32x4_t col3 = vmulq_f32(vld1q_f32(&mat->elems[12]), scaler);

    vst1q_f32(&mOut->elems[0], col0);
    vst1q_f32(&mOut->elems[4], col1);
    vst1q_f32(&mOut->elems[8], col2);
    vst1q_f32(&mOut->elems[12], col3);

    return NML_SUCCESS;

#elif defined(USE_SIMD__SSE)
    __m128 scaler = _mm_set1_ps(s);

    __m128 col0 = _mm_mul_ps(_mm_load_ps(&mat->elems[0]), scaler);
    __m128 col1 = _mm_mul_ps(_mm_load_ps(&mat->elems[4]), scaler);
    __m128 col2 = _mm_mul_ps(_mm_load_ps(&mat->elems[8]), scaler);
    __m128 col3 = _mm_mul_ps(_mm_load_ps(&mat->elems[12]), scaler);

    _mm_store_ps(&mOut->elems[0], col0);
    _mm_store_ps(&mOut->elems[4], col1);
    _mm_store_ps(&mOut->elems[8], col2);
    _mm_store_ps(&mOut->elems[12], col3);

    return NML_SUCCESS;

#else
    for (int i = 0; i < 16; i++) {
        mOut->elems[i] = mat->elems[i] * s;
    }

    return NML_SUCCESS;

#endif
}

int mat4Negate(Mat4 *mat, Mat4 *mOut) {
    NULL_POINTERS(mat, mOut);
#if defined(USE_SIMD__NEON)
    float32x4_t sign_mask = vdupq_n_f32(-0.0f);

    float32x4_t col0 = vreinterpretq_f32_u32(
        veorq_u32(vreinterpretq_u32_f32(vld1q_f32(&mat->elems[0])),
                  vreinterpretq_u32_f32(sign_mask)));
    float32x4_t col1 = vreinterpretq_f32_u32(
        veorq_u32(vreinterpretq_u32_f32(vld1q_f32(&mat->elems[4])),
                  vreinterpretq_u32_f32(sign_mask)));
    float32x4_t col2 = vreinterpretq_f32_u32(
        veorq_u32(vreinterpretq_u32_f32(vld1q_f32(&mat->elems[8])),
                  vreinterpretq_u32_f32(sign_mask)));
    float32x4_t col3 = vreinterpretq_f32_u32(
        veorq_u32(vreinterpretq_u32_f32(vld1q_f32(&mat->elems[12])),
                  vreinterpretq_u32_f32(sign_mask)));

    vst1q_f32(&mOut->elems[0], col0);
    vst1q_f32(&mOut->elems[4], col1);
    vst1q_f32(&mOut->elems[8], col2);
    vst1q_f32(&mOut->elems[12], col3);

    return NML_SUCCESS;

#elif defined(USE_SIMD__SSE)
    __m128 sign_mask = _mm_set1_ps(-0.0f);

    __m128 col0 = _mm_xor_ps(_mm_load_ps(&mat->elems[0]), sign_mask);
    __m128 col1 = _mm_xor_ps(_mm_load_ps(&mat->elems[4]), sign_mask);
    __m128 col2 = _mm_xor_ps(_mm_load_ps(&mat->elems[8]), sign_mask);
    __m128 col3 = _mm_xor_ps(_mm_load_ps(&mat->elems[12]), sign_mask);

    _mm_store_ps(&mOut->elems[0], col0);
    _mm_store_ps(&mOut->elems[4], col1);
    _mm_store_ps(&mOut->elems[8], col2);
    _mm_store_ps(&mOut->elems[12], col3);

    return NML_SUCCESS;

#else
    for (int i = 0; i < 16; i++) {
        mOut->elems[i] = -mat->elems[i];
    }

    return NML_SUCCESS;

#endif
}

int mat4Hadamard(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
#if defined(USE_SIMD__NEON)
    float32x4_t col0 =
        vmulq_f32(vld1q_f32(&mat1->elems[0]), vld1q_f32(&mat2->elems[0]));
    float32x4_t col1 =
        vmulq_f32(vld1q_f32(&mat1->elems[4]), vld1q_f32(&mat2->elems[4]));
    float32x4_t col2 =
        vmulq_f32(vld1q_f32(&mat1->elems[8]), vld1q_f32(&mat2->elems[8]));
    float32x4_t col3 = vmulq_f32(vld1q_f32(&mat1->elems[12]),
                                 vld1q_f32(&mat2->elems[12]));

    vst1q_f32(&mOut->elems[0], col0);
    vst1q_f32(&mOut->elems[4], col1);
    vst1q_f32(&mOut->elems[8], col2);
    vst1q_f32(&mOut->elems[12], col3);

    return NML_SUCCESS;

#elif defined(USE_SIMD__SSE)
    __m128 col0 = _mm_mul_ps(_mm_load_ps(&mat1->elems[0], _mm_load_ps(&mat2->elems[0]);
    __m128 col1 = _mm_mul_ps(_mm_load_ps(&mat1->elems[4], _mm_load_ps(&mat2->elems[4]);
    __m128 col2 = _mm_mul_ps(_mm_load_ps(&mat1->elems[8], _mm_load_ps(&mat2->elems[8]);
    __m128 col3 = _mm_mul_ps(_mm_load_ps(&mat1->elems[12], _mm_load_ps(&mat2->elems[12]);

    _mm_store_ps(&mOut->elems[0], col0);
    _mm_store_ps(&mOut->elems[4], col1);
    _mm_store_ps(&mOut->elems[8], col2);
    _mm_store_ps(&mOut->elems[12], col3);

    return NML_SUCCESS;
#else
    NULL_POINTERS(mat1, mat2, mOut);
    for (int i = 0; i < 16; i++) {
        mOut->elems[i] = mat1->elems[i] * mat2->elems[i];
    }

    return NML_SUCCESS;

#endif
}

int mat4MulVec4(Mat4 *mat, Vec4 *vec, Vec4 *vOut) {
    NULL_POINTERS(mat, vec, vOut);
#if defined(USE_SIMD__NEON)
    float32x4_t v = vld1q_f32(vec->elems);

    float32x4_t res =
        vmulq_lane_f32(vld1q_f32(mat->cols[0].elems), vget_low_f32(v), 0);
    res = vmlaq_lane_f32(
        res, vld1q_f32(mat->cols[1].elems), vget_low_f32(v), 1);
    res = vmlaq_lane_f32(
        res, vld1q_f32(mat->cols[2].elems), vget_high_f32(v), 0);
    res = vmlaq_lane_f32(
        res, vld1q_f32(mat->cols[3].elems), vget_high_f32(v), 1);

    vst1q_f32(vOut->elems, res);

    return NML_SUCCESS;

#elif defined(USE_SIMD__SSE)
    __m128 v = _mm_load_ps(vec->elems);

    __m128 res = _mm_mul_ps(_mm_load_ps(mat->cols[0].elems),
                            _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0)));
    res = _mm_add_ps(res,
                     _mm_mul_ps(_mm_load_ps(mat->cols[1].elems),
                                _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1))));
    res = _mm_add_ps(res,
                     _mm_mul_ps(_mm_load_ps(mat->cols[2].elems),
                                _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2))));
    res = _mm_add_ps(res,
                     _mm_mul_ps(_mm_load_ps(mat->cols[3].elems),
                                _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3))));

    _mm_store_ps(vOut->elems, res);

    return NML_SUCCESS;

#else
    vOut->x = vec->elems[0] * mat->cols[0].x +
              vec->elems[1] * mat->cols[1].x +
              vec->elems[2] * mat->cols[2].x +
              vec->elems[3] * mat->cols[3].x;
    vOut->y = vec->elems[0] * mat->cols[0].y +
              vec->elems[1] * mat->cols[1].y +
              vec->elems[2] * mat->cols[2].y +
              vec->elems[3] * mat->cols[3].y;
    vOut->z = vec->elems[0] * mat->cols[0].z +
              vec->elems[1] * mat->cols[1].z +
              vec->elems[2] * mat->cols[2].z +
              vec->elems[3] * mat->cols[3].z;

    vOut->w = vec->elems[0] * mat->cols[0].w +
              vec->elems[1] * mat->cols[1].w +
              vec->elems[2] * mat->cols[2].w +
              vec->elems[3] * mat->cols[3].w;

    return NML_SUCCESS;

#endif
}

int mat4MulMat4(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
#if defined(USE_SIMD__NEON)
    float32x4_t mat1_col0 = vld1q_f32(&mat1->cols[0].x);
    float32x4_t mat1_col1 = vld1q_f32(&mat1->cols[1].x);
    float32x4_t mat1_col2 = vld1q_f32(&mat1->cols[2].x);
    float32x4_t mat1_col3 = vld1q_f32(&mat1->cols[3].x);

    for (int i = 0; i < 4; i++) {
        float32x4_t mat2_col = vld1q_f32(&mat2->cols[i].x);

        float32x4_t bc0 = vdupq_n_f32(vgetq_lane_f32(mat2_col, 0));
        float32x4_t bc1 = vdupq_n_f32(vgetq_lane_f32(mat2_col, 1));
        float32x4_t bc2 = vdupq_n_f32(vgetq_lane_f32(mat2_col, 2));
        float32x4_t bc3 = vdupq_n_f32(vgetq_lane_f32(mat2_col, 3));

        float32x4_t result = vmulq_f32(mat1_col0, bc0);
        result = vmlaq_f32(result, mat1_col1, bc1);
        result = vmlaq_f32(result, mat1_col2, bc2);
        result = vmlaq_f32(result, mat1_col3, bc3);

        vst1q_f32(&mOut->cols[i].x, result);
    }

    return NML_SUCCESS;

#elif defined(USE_SIMD__SSE)
    __m128 mat1_col0 = _mm_load_ps(&mat1->cols[0].x);
    __m128 mat1_col1 = _mm_load_ps(&mat1->cols[1].x);
    __m128 mat1_col2 = _mm_load_ps(&mat1->cols[2].x);
    __m128 mat1_col3 = _mm_load_ps(&mat1->cols[3].x);

    for (int i = 0; i < 4; i++) {
        __m128 mat2_col = _mm_load_ps(&mat2->cols[i].x);

        __m128 bc0 = _mm_set1_ps(_mm_cvtss_f32(mat2_col));
        __m128 bc1 = _mm_set1_ps(_mm_cvtss_f32(
            _mm_shuffle_ps(mat2_col, mat2_col, _MM_SHUFFLE(1, 1, 1, 1))));
        __m128 bc2 = _mm_set1_ps(_mm_cvtss_f32(
            _mm_shuffle_ps(mat2_col, mat2_col, _MM_SHUFFLE(2, 2, 2, 2))));
        __m128 bc3 = _mm_set1_ps(_mm_cvtss_f32(
            _mm_shuffle_ps(mat2_col, mat2_col, _MM_SHUFFLE(3, 3, 3, 3))));

        __m128 result = _mm_mul_ps(mat1_col0, bc0);
        result = _mm_add_ps(result, _mm_mul_ps(mat1_col1, bc1));
        result = _mm_add_ps(result, _mm_mul_ps(mat1_col2, bc2));
        result = _mm_add_ps(result, _mm_mul_ps(mat1_col3, bc3));

        _mm_store_ps(&mOut->cols[i].x, result);
    }

    return NML_SUCCESS;
#else
    mat4MulVec4(mat1, &mat2->cols[0], &mOut->cols[0]);
    mat4MulVec4(mat1, &mat2->cols[1], &mOut->cols[1]);
    mat4MulVec4(mat1, &mat2->cols[2], &mOut->cols[2]);
    mat4MulVec4(mat1, &mat2->cols[3], &mOut->cols[3]);

    return NML_SUCCESS;

#endif
}
