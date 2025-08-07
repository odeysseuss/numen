#include "vector/vec4d.h"
#include "utils/math.h"
#include "utils/errors.h"

int Vec4Init(nml_t x, nml_t y, nml_t z, nml_t w, Vec4 *vOut) {
    vOut->X = x;
    vOut->Y = y;
    vOut->Z = z;
    vOut->W = w;
    return NML_SUCCESS;
}

int Vec4InitZero(Vec4 *vOut) {
    return Vec4Init(0.0, 0.0, 0.0, 0.0, vOut);
}

nml_t Vec4Length(Vec4 *vec) {
    return sqrt(Sqr(vec->X) + Sqr(vec->Y) + Sqr(vec->Z) + Sqr(vec->W));
}

nml_t Vec4LengthSqr(Vec4 *vec) {
    return Sqr(vec->X) + Sqr(vec->Y) + Sqr(vec->Z) + Sqr(vec->W);
}

int Vec4Normalize(Vec4 *vec, Vec4 *vOut) {
    if (Vec4IsZero(vec))
        return NML_EZERODIV;

    nml_t l = Vec4Length(vec);
    vOut->X = vec->X / l;
    vOut->Y = vec->Y / l;
    vOut->Z = vec->Z / l;
    vOut->W = vec->W / l;
    return NML_SUCCESS;
}

nml_t Vec4Dot(Vec4 *vec1, Vec4 *vec2) {
    return (vec1->X * vec2->X + vec1->Y * vec2->Y + vec1->Z * vec2->Z +
            vec1->W * vec2->W);
}

int Vec4Cross(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    vOut->X = (vec1->Y * vec2->Z) - (vec1->Z * vec2->Y);
    vOut->Y = (vec1->Z * vec2->X) - (vec1->X * vec2->Z);
    vOut->Z = (vec1->X * vec2->Y) - (vec1->Y * vec2->X);
    vOut->W = 0.0f;
    return NML_SUCCESS;
}

int Vec4Add(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    vOut->X = vec1->X + vec2->X;
    vOut->Y = vec1->Y + vec2->Y;
    vOut->Z = vec1->Z + vec2->Z;
    vOut->W = vec1->W + vec2->W;
    return NML_SUCCESS;
}

int Vec4Sub(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    vOut->X = vec1->X - vec2->X;
    vOut->Y = vec1->Y - vec2->Y;
    vOut->Z = vec1->Z - vec2->Z;
    vOut->W = vec1->W - vec2->W;
    return NML_SUCCESS;
}

int Vec4Mul(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    vOut->X = vec1->X * vec2->X;
    vOut->Y = vec1->Y * vec2->Y;
    vOut->Z = vec1->Z * vec2->Z;
    vOut->W = vec1->W * vec2->W;
    return NML_SUCCESS;
}

int Vec4Div(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    if (fabs(vec2->X) < kEPSILON || fabs(vec2->Y) < kEPSILON ||
        fabs(vec2->Z) < kEPSILON || fabs(vec2->W) < kEPSILON) {
        return NML_EZERODIV;
    }

    vOut->X = vec1->X / vec2->X;
    vOut->Y = vec1->Y / vec2->Y;
    vOut->Z = vec1->Z / vec2->Z;
    vOut->W = vec1->W / vec2->W;
    return NML_SUCCESS;
}

int Vec4Scale(Vec4 *vec, nml_t s, Vec4 *vOut) {
    vOut->X = vec->X * s;
    vOut->Y = vec->Y * s;
    vOut->Z = vec->Z * s;
    vOut->W = vec->W * s;
    return NML_SUCCESS;
}

int Vec4Negate(Vec4 *vec, Vec4 *vOut) {
    vOut->X = -vec->X;
    vOut->Y = -vec->Y;
    vOut->Z = -vec->Z;
    vOut->W = -vec->W;
    return NML_SUCCESS;
}

int Vec4Project(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    nml_t lenSqr = Vec4LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t scaler = Vec4Dot(vec1, vec2) / lenSqr;
    vOut->X = vec2->X * scaler;
    vOut->Y = vec2->Y * scaler;
    vOut->Z = vec2->Z * scaler;
    vOut->W = vec2->W * scaler;
    return NML_SUCCESS;
}

int Vec4Reject(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    nml_t lenSqr = Vec4LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t dot = Vec4Dot(vec1, vec2);
    nml_t scaler = dot / lenSqr;

    vOut->X = vec1->X - (scaler * vec2->X);
    vOut->Y = vec1->Y - (scaler * vec2->Y);
    vOut->Z = vec1->Z - (scaler * vec2->Z);
    vOut->W = vec1->W - (scaler * vec2->W);
    return NML_SUCCESS;
}

int Vec4Reflect(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut) {
    nml_t lenSqr = Vec4LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t scaler = 2.0 * Vec4Dot(vec1, vec2) / lenSqr;
    vOut->X = vec1->X - scaler * vec2->X;
    vOut->Y = vec1->Y - scaler * vec2->Y;
    vOut->Z = vec1->Z - scaler * vec2->Z;
    vOut->W = vec1->W - scaler * vec2->W;
    return NML_SUCCESS;
}
