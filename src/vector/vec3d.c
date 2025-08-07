#include "vector/vec3d.h"
#include "utils/math.h"
#include "utils/errors.h"

int Vec3Init(nml_t x, nml_t y, nml_t z, Vec3 *vOut) {
    vOut->X = x;
    vOut->Y = y;
    vOut->Z = z;
    return NML_SUCCESS;
}

int Vec3InitZero(Vec3 *vOut) {
    return Vec3Init(0.0, 0.0, 0.0, vOut);
}

nml_t Vec3Length(Vec3 *vec) {
    return sqrt(Sqr(vec->X) + Sqr(vec->Y) + Sqr(vec->Z));
}

nml_t Vec3LengthSqr(Vec3 *vec) {
    return Sqr(vec->X) + Sqr(vec->Y) + Sqr(vec->Z);
}

int Vec3Normalize(Vec3 *vec, Vec3 *vOut) {
    if (Vec3IsZero(vec))
        return NML_EZERODIV;
    nml_t l = 1.0 / Vec3Length(vec);
    vOut->X = vec->X * l;
    vOut->Y = vec->Y * l;
    vOut->Z = vec->Z * l;
    return NML_SUCCESS;
}

nml_t Vec3Dot(Vec3 *vec1, Vec3 *vec2) {
    return (vec1->X * vec2->X + vec1->Y * vec2->Y + vec1->Z * vec2->Z);
}

int Vec3Cross(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut) {
    vOut->X = (vec1->Y * vec2->Z) - (vec1->Z * vec2->Y);
    vOut->Y = (vec1->Z * vec2->X) - (vec1->X * vec2->Z);
    vOut->Z = (vec1->X * vec2->Y) - (vec1->Y * vec2->X);
    return NML_SUCCESS;
}

int Vec3Add(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut) {
    vOut->X = vec1->X + vec2->X;
    vOut->Y = vec1->Y + vec2->Y;
    vOut->Z = vec1->Z + vec2->Z;
    return NML_SUCCESS;
}

int Vec3Sub(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut) {
    vOut->X = vec1->X - vec2->X;
    vOut->Y = vec1->Y - vec2->Y;
    vOut->Z = vec1->Z - vec2->Z;
    return NML_SUCCESS;
}

int Vec3Mul(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut) {
    vOut->X = vec1->X * vec2->X;
    vOut->Y = vec1->Y * vec2->Y;
    vOut->Z = vec1->Z * vec2->Z;
    return NML_SUCCESS;
}

int Vec3Div(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut) {
    if (fabs(vec2->X) < kEPSILON || fabs(vec2->Y) < kEPSILON ||
        fabs(vec2->Z) < kEPSILON) {
        return NML_EZERODIV;
    }

    vOut->X = vec1->X / vec2->X;
    vOut->Y = vec1->Y / vec2->Y;
    vOut->Z = vec1->Z / vec2->Z;
    return NML_SUCCESS;
}

int Vec3Scale(Vec3 *vec, nml_t s, Vec3 *vOut) {
    vOut->X = vec->X * s;
    vOut->Y = vec->Y * s;
    vOut->Z = vec->Z * s;
    return NML_SUCCESS;
}

int Vec3Negate(Vec3 *vec, Vec3 *vOut) {
    vOut->X = -vec->X;
    vOut->Y = -vec->Y;
    vOut->Z = -vec->Z;
    return NML_SUCCESS;
}

int Vec3Project(Vec3 *vec1, Vec3 *vec3, Vec3 *vOut) {
    nml_t lenSqr = Vec3LengthSqr(vec3);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t scaler = Vec3Dot(vec1, vec3) / lenSqr;
    vOut->X = vec3->X * scaler;
    vOut->Y = vec3->Y * scaler;
    vOut->Z = vec3->Z * scaler;
    return NML_SUCCESS;
}

int Vec3Reject(Vec3 *vec1, Vec3 *vec3, Vec3 *vOut) {
    nml_t lenSqr = Vec3LengthSqr(vec3);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t dot = Vec3Dot(vec1, vec3);
    nml_t scaler = dot / lenSqr;

    vOut->X = vec1->X - (scaler * vec3->X);
    vOut->Y = vec1->Y - (scaler * vec3->Y);
    vOut->Z = vec1->Z - (scaler * vec3->Z);
    return NML_SUCCESS;
}

int Vec3Reflect(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut) {
    nml_t lenSqr = Vec3LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t scaler = 2.0 * Vec3Dot(vec1, vec2) / lenSqr;
    vOut->X = vec1->X - scaler * vec2->X;
    vOut->Y = vec1->Y - scaler * vec2->Y;
    vOut->Z = vec1->Z - scaler * vec2->Z;
    return NML_SUCCESS;
}
