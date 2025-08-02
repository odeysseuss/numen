#include "vector/vec4d.h"
#include "utils/math.h"
#include "utils/errors.h"

int Vec4Init(nml_t x, nml_t y, nml_t z, nml_t w, Vec4 *vOut) {
    vOut->x = x;
    vOut->y = y;
    vOut->z = z;
    vOut->w = w;
    return NML_SUCCESS;
}

int Vec4InitZero(Vec4 *vOut) {
    return Vec4Init(0.0, 0.0, 0.0, 0.0, vOut);
}

nml_t Vec4Length(Vec4 *vec) {
    return sqrt(Sqr(vec->x) + Sqr(vec->y) + Sqr(vec->z) + Sqr(vec->w));
}

nml_t Vec4LengthSqr(Vec4 *vec) {
    return Sqr(vec->x) + Sqr(vec->y) + Sqr(vec->z) + Sqr(vec->w);
}

int Vec4Normalize(Vec4 *vec, Vec4 *vOut) {
    if (Vec4IsZero(vec))
        return NML_EZERODIV;

    nml_t l = 1.0 / Vec4Length(vec);
    vOut->x = vec->x * l;
    vOut->y = vec->y * l;
    vOut->z = vec->z * l;
    vOut->w = vec->w * l;
    return NML_SUCCESS;
}

nml_t Vec4Dot(Vec4 *vec1, Vec4 *vec2) {
    return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z +
            vec1->w * vec2->w);
}

int Vec4Cross(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    vOut->x = (vec1->y * vec2->z) - (vec1->z * vec2->y);
    vOut->y = (vec1->z * vec2->x) - (vec1->x * vec2->z);
    vOut->z = (vec1->x * vec2->y) - (vec1->y * vec2->x);
    vOut->w = 0.0f;
    return NML_SUCCESS;
}

int Vec4Add(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    vOut->x = vec1->x + vec2->x;
    vOut->y = vec1->y + vec2->y;
    vOut->z = vec1->z + vec2->z;
    vOut->w = vec1->w + vec2->w;
    return NML_SUCCESS;
}

int Vec4Sub(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    vOut->x = vec1->x - vec2->x;
    vOut->y = vec1->y - vec2->y;
    vOut->z = vec1->z - vec2->z;
    vOut->w = vec1->w - vec2->w;
    return NML_SUCCESS;
}

int Vec4Mul(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    vOut->x = vec1->x * vec2->x;
    vOut->y = vec1->y * vec2->y;
    vOut->z = vec1->z * vec2->z;
    vOut->w = vec1->w * vec2->w;
    return NML_SUCCESS;
}

int Vec4Div(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    if (fabs(vec2->x) < kEPSILON || fabs(vec2->y) < kEPSILON ||
        fabs(vec2->z) < kEPSILON || fabs(vec2->w) < kEPSILON) {
        return NML_EZERODIV;
    }

    vOut->x = vec1->x / vec2->x;
    vOut->y = vec1->y / vec2->y;
    vOut->z = vec1->z / vec2->z;
    vOut->w = vec1->w / vec2->w;
    return NML_SUCCESS;
}

int Vec4Scale(Vec4 *vec, nml_t s, Vec4 *vOut) {
    vOut->x = vec->x * s;
    vOut->y = vec->y * s;
    vOut->z = vec->z * s;
    vOut->w = vec->w * s;
    return NML_SUCCESS;
}

int Vec4Negate(Vec4 *vec, Vec4 *vOut) {
    vOut->x = -vec->x;
    vOut->y = -vec->y;
    vOut->z = -vec->z;
    vOut->w = -vec->w;
    return NML_SUCCESS;
}

int Vec4Project(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    nml_t lenSqr = Vec4LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t scaler = Vec4Dot(vec1, vec2) / lenSqr;
    vOut->x = vec2->x * scaler;
    vOut->y = vec2->y * scaler;
    vOut->z = vec2->z * scaler;
    vOut->w = vec2->w * scaler;
    return NML_SUCCESS;
}

int Vec4Reject(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    nml_t lenSqr = Vec4LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t dot = Vec4Dot(vec1, vec2);
    nml_t scaler = dot / lenSqr;

    vOut->x = vec1->x - (scaler * vec2->x);
    vOut->y = vec1->y - (scaler * vec2->y);
    vOut->z = vec1->z - (scaler * vec2->z);
    vOut->w = vec1->w - (scaler * vec2->w);
    return NML_SUCCESS;
}

int Vec4Reflect(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    nml_t lenSqr = Vec4LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t scaler = 2.0 * Vec4Dot(vec1, vec2) / lenSqr;
    vOut->x = vec1->x - scaler * vec2->x;
    vOut->y = vec1->y - scaler * vec2->y;
    vOut->z = vec1->z - scaler * vec2->z;
    vOut->w = vec1->w - scaler * vec2->w;
    return NML_SUCCESS;
}
