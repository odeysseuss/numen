#include "matrix/mat4d.h"
#include "utils/errors.h"
#include "utils/simd.h"
#include <string.h>

int Mat4Init(const nml_t arr[16], Mat4 *mOut) {
    NULL_POINTERS(mOut);
    memcpy(mOut->Elements, arr, sizeof(nml_t) * 16);
    return NML_SUCCESS;
}

int Mat4InitZero(Mat4 *mOut) {
    NULL_POINTERS(mOut);
    memset(mOut, 0, sizeof(Mat4));
    return NML_SUCCESS;
}

int Mat4Diagonal(nml_t val, Mat4 *mOut) {
    NULL_POINTERS(mOut);
    memset(mOut->Elements, 0, sizeof(Mat4));
    for (int i = 0; i < 4; i++) {
        mOut->Elements[i * 4 + i] = val;
    }

    return NML_SUCCESS;
}

int Mat4Identity(Mat4 *mOut) {
    NULL_POINTERS(mOut);
    memset(mOut->Elements, 0, sizeof(Mat4));
    for (int i = 0; i < 4; i++) {
        mOut->Elements[i * 4 + i] = 1.0;
    }

    return NML_SUCCESS;
}

int Mat4Add(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
#if defined(USE_SIMD__NEON)
    float32x4_t col0 =
        vaddq_f32(vld1q_f32(&mat1->Elements[0]), vld1q_f32(&mat2->Elements[0]));
    float32x4_t col1 =
        vaddq_f32(vld1q_f32(&mat1->Elements[4]), vld1q_f32(&mat2->Elements[4]));
    float32x4_t col2 =
        vaddq_f32(vld1q_f32(&mat1->Elements[8]), vld1q_f32(&mat2->Elements[8]));
    float32x4_t col3 = vaddq_f32(vld1q_f32(&mat1->Elements[12]),
                                 vld1q_f32(&mat2->Elements[12]));

    vst1q_f32(&mOut->Elements[0], col0);
    vst1q_f32(&mOut->Elements[4], col1);
    vst1q_f32(&mOut->Elements[8], col2);
    vst1q_f32(&mOut->Elements[12], col3);

    return NML_SUCCESS;

#elif defined(USE_SIMD__SSE)
    __m128 col0 = _mm_add_ps(_mm_load_ps(&mat1->Elements[0]),
                             _mm_load_ps(&mat2->Elements[0]));
    __m128 col1 = _mm_add_ps(_mm_load_ps(&mat1->Elements[4]),
                             _mm_load_ps(&mat2->Elements[4]));
    __m128 col2 = _mm_add_ps(_mm_load_ps(&mat1->Elements[8]),
                             _mm_load_ps(&mat2->Elements[8]));
    __m128 col3 = _mm_add_ps(_mm_load_ps(&mat1->Elements[12]),
                             _mm_load_ps(&mat2->Elements[12]));

    _mm_store_ps(&mOut->Elements[0], col0);
    _mm_store_ps(&mOut->Elements[4], col1);
    _mm_store_ps(&mOut->Elements[8], col2);
    _mm_store_ps(&mOut->Elements[12], col3);

    return NML_SUCCESS;

#else
    for (int i = 0; i < 16; i++) {
        mOut->Elements[i] = mat1->Elements[i] + mat2->Elements[i];
    }

    return NML_SUCCESS;

#endif
}

int Mat4Sub(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
#if defined(USE_SIMD__NEON)
    float32x4_t col0 =
        vsubq_f32(vld1q_f32(&mat1->Elements[0]), vld1q_f32(&mat2->Elements[0]));
    float32x4_t col1 =
        vsubq_f32(vld1q_f32(&mat1->Elements[4]), vld1q_f32(&mat2->Elements[4]));
    float32x4_t col2 =
        vsubq_f32(vld1q_f32(&mat1->Elements[8]), vld1q_f32(&mat2->Elements[8]));
    float32x4_t col3 = vsubq_f32(vld1q_f32(&mat1->Elements[12]),
                                 vld1q_f32(&mat2->Elements[12]));

    vst1q_f32(&mOut->Elements[0], col0);
    vst1q_f32(&mOut->Elements[4], col1);
    vst1q_f32(&mOut->Elements[8], col2);
    vst1q_f32(&mOut->Elements[12], col3);

    return NML_SUCCESS;

#elif defined(USE_SIMD__SSE)
    __m128 col0 = _mm_sub_ps(_mm_load_ps(&mat1->Elements[0]),
                             _mm_load_ps(&mat2->Elements[0]));
    __m128 col1 = _mm_sub_ps(_mm_load_ps(&mat1->Elements[4]),
                             _mm_load_ps(&mat2->Elements[4]));
    __m128 col2 = _mm_sub_ps(_mm_load_ps(&mat1->Elements[8]),
                             _mm_load_ps(&mat2->Elements[8]));
    __m128 col3 = _mm_sub_ps(_mm_load_ps(&mat1->Elements[12]),
                             _mm_load_ps(&mat2->Elements[12]));

    _mm_store_ps(&mOut->Elements[0], col0);
    _mm_store_ps(&mOut->Elements[4], col1);
    _mm_store_ps(&mOut->Elements[8], col2);
    _mm_store_ps(&mOut->Elements[12], col3);

    return NML_SUCCESS;

#else
    for (int i = 0; i < 16; i++) {
        mOut->Elements[i] = mat1->Elements[i] - mat2->Elements[i];
    }

    return NML_SUCCESS;

#endif
}

int Mat4Scale(Mat4 *mat, nml_t s, Mat4 *mOut) {
    NULL_POINTERS(mat, mOut);
#if defined(USE_SIMD__NEON)
    float32x4_t scaler = vdupq_n_f32(s);

    float32x4_t col0 = vmulq_f32(vld1q_f32(&mat->Elements[0]), scaler);
    float32x4_t col1 = vmulq_f32(vld1q_f32(&mat->Elements[4]), scaler);
    float32x4_t col2 = vmulq_f32(vld1q_f32(&mat->Elements[8]), scaler);
    float32x4_t col3 = vmulq_f32(vld1q_f32(&mat->Elements[12]), scaler);

    vst1q_f32(&mOut->Elements[0], col0);
    vst1q_f32(&mOut->Elements[4], col1);
    vst1q_f32(&mOut->Elements[8], col2);
    vst1q_f32(&mOut->Elements[12], col3);

    return NML_SUCCESS;

#elif defined(USE_SIMD__SSE)
    __m128 scaler = _mm_set1_ps(s);

    __m128 col0 = _mm_mul_ps(_mm_load_ps(&mat->Elements[0]), scaler);
    __m128 col1 = _mm_mul_ps(_mm_load_ps(&mat->Elements[4]), scaler);
    __m128 col2 = _mm_mul_ps(_mm_load_ps(&mat->Elements[8]), scaler);
    __m128 col3 = _mm_mul_ps(_mm_load_ps(&mat->Elements[12]), scaler);

    _mm_store_ps(&mOut->Elements[0], col0);
    _mm_store_ps(&mOut->Elements[4], col1);
    _mm_store_ps(&mOut->Elements[8], col2);
    _mm_store_ps(&mOut->Elements[12], col3);

    return NML_SUCCESS;

#else
    for (int i = 0; i < 16; i++) {
        mOut->Elements[i] = mat->Elements[i] * s;
    }

    return NML_SUCCESS;

#endif
}

int Mat4Negate(Mat4 *mat, Mat4 *mOut) {
    NULL_POINTERS(mat, mOut);
#if defined(USE_SIMD__NEON)
    float32x4_t sign_mask = vdupq_n_f32(-0.0f);

    float32x4_t col0 = vreinterpretq_f32_u32(
        veorq_u32(vreinterpretq_u32_f32(vld1q_f32(&mat->Elements[0])),
                  vreinterpretq_u32_f32(sign_mask)));
    float32x4_t col1 = vreinterpretq_f32_u32(
        veorq_u32(vreinterpretq_u32_f32(vld1q_f32(&mat->Elements[4])),
                  vreinterpretq_u32_f32(sign_mask)));
    float32x4_t col2 = vreinterpretq_f32_u32(
        veorq_u32(vreinterpretq_u32_f32(vld1q_f32(&mat->Elements[8])),
                  vreinterpretq_u32_f32(sign_mask)));
    float32x4_t col3 = vreinterpretq_f32_u32(
        veorq_u32(vreinterpretq_u32_f32(vld1q_f32(&mat->Elements[12])),
                  vreinterpretq_u32_f32(sign_mask)));

    vst1q_f32(&mOut->Elements[0], col0);
    vst1q_f32(&mOut->Elements[4], col1);
    vst1q_f32(&mOut->Elements[8], col2);
    vst1q_f32(&mOut->Elements[12], col3);

    return NML_SUCCESS;

#elif defined(USE_SIMD__SSE)
    __m128 sign_mask = _mm_set1_ps(-0.0f);

    __m128 col0 = _mm_xor_ps(_mm_load_ps(&mat->Elements[0], sign_mask);
    __m128 col1 = _mm_xor_ps(_mm_load_ps(&mat->Elements[4], sign_mask);
    __m128 col2 = _mm_xor_ps(_mm_load_ps(&mat->Elements[8], sign_mask);
    __m128 col3 = _mm_xor_ps(_mm_load_ps(&mat->Elements[12], sign_mask);

    _mm_store_ps(&mOut->Elements[0], col0);
    _mm_store_ps(&mOut->Elements[4], col1);
    _mm_store_ps(&mOut->Elements[8], col2);
    _mm_store_ps(&mOut->Elements[12], col3);

    return NML_SUCCESS;

#else
    for (int i = 0; i < 16; i++) {
        mOut->Elements[i] = -mat->Elements[i];
    }

    return NML_SUCCESS;

#endif
}

int Mat4Hadamard(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
#if defined(USE_SIMD__NEON)
    float32x4_t col0 =
        vmulq_f32(vld1q_f32(&mat1->Elements[0]), vld1q_f32(&mat2->Elements[0]));
    float32x4_t col1 =
        vmulq_f32(vld1q_f32(&mat1->Elements[4]), vld1q_f32(&mat2->Elements[4]));
    float32x4_t col2 =
        vmulq_f32(vld1q_f32(&mat1->Elements[8]), vld1q_f32(&mat2->Elements[8]));
    float32x4_t col3 = vmulq_f32(vld1q_f32(&mat1->Elements[12]),
                                 vld1q_f32(&mat2->Elements[12]));

    vst1q_f32(&mOut->Elements[0], col0);
    vst1q_f32(&mOut->Elements[4], col1);
    vst1q_f32(&mOut->Elements[8], col2);
    vst1q_f32(&mOut->Elements[12], col3);

    return NML_SUCCESS;

#elif defined(USE_SIMD__SSE)
    __m128 col0 = _mm_mul_ps(_mm_load_ps(&mat1->Elements[0], _mm_load_ps(&mat2->Elements[0]);
    __m128 col1 = _mm_mul_ps(_mm_load_ps(&mat1->Elements[4], _mm_load_ps(&mat2->Elements[4]);
    __m128 col2 = _mm_mul_ps(_mm_load_ps(&mat1->Elements[8], _mm_load_ps(&mat2->Elements[8]);
    __m128 col3 = _mm_mul_ps(_mm_load_ps(&mat1->Elements[12], _mm_load_ps(&mat2->Elements[12]);

    _mm_store_ps(&mOut->Elements[0], col0);
    _mm_store_ps(&mOut->Elements[4], col1);
    _mm_store_ps(&mOut->Elements[8], col2);
    _mm_store_ps(&mOut->Elements[12], col3);

    return NML_SUCCESS;
#else
    NULL_POINTERS(mat1, mat2, mOut);
    for (int i = 0; i < 16; i++) {
        mOut->Elements[i] = mat1->Elements[i] * mat2->Elements[i];
    }

    return NML_SUCCESS;

#endif
}

int Mat4MulVec4(Mat4 *mat, Vec4 *vec, Vec4 *vOut) {
    NULL_POINTERS(mat, vec, vOut);
#if defined(USE_SIMD__NEON)
    float32x4_t v = vld1q_f32(vec->Elements);

    float32x4_t res =
        vmulq_lane_f32(vld1q_f32(mat->Columns[0].Elements), vget_low_f32(v), 0);
    res = vmlaq_lane_f32(
        res, vld1q_f32(mat->Columns[1].Elements), vget_low_f32(v), 1);
    res = vmlaq_lane_f32(
        res, vld1q_f32(mat->Columns[2].Elements), vget_high_f32(v), 0);
    res = vmlaq_lane_f32(
        res, vld1q_f32(mat->Columns[3].Elements), vget_high_f32(v), 1);

    vst1q_f32(vOut->Elements, res);

    return NML_SUCCESS;

#elif defined(USE_SIMD_SSE)
    __m128 v = _mm_load_ps(vec->Elements);

    __m128 res = _mm_mul_ps(_mm_load_ps(mat->Columns[0].Elements),
                            _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0)));
    res = _mm_add_ps(res,
                     _mm_mul_ps(_mm_load_ps(mat->Columns[1].Elements),
                                _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1))));
    res = _mm_add_ps(res,
                     _mm_mul_ps(_mm_load_ps(mat->Columns[2].Elements),
                                _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2))));
    res = _mm_add_ps(res,
                     _mm_mul_ps(_mm_load_ps(mat->Columns[3].Elements),
                                _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3))));

    _mm_store_ps(vOut->Elements, res);

    return NML_SUCCESS;

#else
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

#endif
}

int Mat4MulMat4(Mat4 *mat1, Mat4 *mat2, Mat4 *mOut) {
    NULL_POINTERS(mat1, mat2, mOut);
#if defined(USE_SIMD__NEON)
    float32x4_t mat1_col0 = vld1q_f32(&mat1->Columns[0].x);
    float32x4_t mat1_col1 = vld1q_f32(&mat1->Columns[1].x);
    float32x4_t mat1_col2 = vld1q_f32(&mat1->Columns[2].x);
    float32x4_t mat1_col3 = vld1q_f32(&mat1->Columns[3].x);

    for (int i = 0; i < 4; i++) {
        float32x4_t mat2_col = vld1q_f32(&mat2->Columns[i].x);

        float32x4_t bc0 = vdupq_n_f32(vgetq_lane_f32(mat2_col, 0));
        float32x4_t bc1 = vdupq_n_f32(vgetq_lane_f32(mat2_col, 1));
        float32x4_t bc2 = vdupq_n_f32(vgetq_lane_f32(mat2_col, 2));
        float32x4_t bc3 = vdupq_n_f32(vgetq_lane_f32(mat2_col, 3));

        float32x4_t result = vmulq_f32(mat1_col0, bc0);
        result = vmlaq_f32(result, mat1_col1, bc1);
        result = vmlaq_f32(result, mat1_col2, bc2);
        result = vmlaq_f32(result, mat1_col3, bc3);

        vst1q_f32(&mOut->Columns[i].x, result);
    }

    return NML_SUCCESS;

#elif defined(USE_SIMD__SSE)
    __m128 mat1_col0 = _mm_load_ps(&mat1->Columns[0].x);
    __m128 mat1_col1 = _mm_load_ps(&mat1->Columns[1].x);
    __m128 mat1_col2 = _mm_load_ps(&mat1->Columns[2].x);
    __m128 mat1_col3 = _mm_load_ps(&mat1->Columns[3].x);

    for (int i = 0; i < 4; i++) {
        __m128 mat2_col = _mm_load_ps(&mat2->Columns[i].x);

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

        _mm_store_ps(&mOut->Columns[i].x, result);
    }

    return NML_SUCCESS;
#else
    Mat4MulVec4(mat1, &mat2->Columns[0], &mOut->Columns[0]);
    Mat4MulVec4(mat1, &mat2->Columns[1], &mOut->Columns[1]);
    Mat4MulVec4(mat1, &mat2->Columns[2], &mOut->Columns[2]);
    Mat4MulVec4(mat1, &mat2->Columns[3], &mOut->Columns[3]);

    return NML_SUCCESS;

#endif
}
