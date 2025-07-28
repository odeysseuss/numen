#include "vector/vec3d.h"
#include "utils/math.h"
#include "utils/errors.h"

int Vec3Init(nml_t x, nml_t y, nml_t z, Vec3 *vOut) {
    vOut->x = x;
    vOut->y = y;
    vOut->z = z;
    return NML_SUCCESS;
}

int Vec3InitZero(Vec3 *vOut) {
    return Vec3Init(0.0, 0.0, 0.0, vOut);
}

nml_t Vec3Length(Vec3 *vec) {
    return sqrt(Sqr(vec->x) + Sqr(vec->y) + Sqr(vec->z));
}

nml_t Vec3LengthSqr(Vec3 *vec) {
    return Sqr(vec->x) + Sqr(vec->y) + Sqr(vec->z);
}

int Vec3Normalize(Vec3 *vec, Vec3 *vOut) {
    if (Vec3IsZero(vec))
        return NML_EZERODIV;
    nml_t l = 1.0 / Vec3Length(vec);
    vOut->x = vec->x * l;
    vOut->y = vec->y * l;
    vOut->z = vec->z * l;
    return NML_SUCCESS;
}

nml_t Vec3Dot(Vec3 *vec1, Vec3 *vec2) {
    return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}

int Vec3Cross(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut) {
    vOut->x = (vec1->y * vec2->z) - (vec1->z * vec2->y);
    vOut->y = (vec1->z * vec2->x) - (vec1->x * vec2->z);
    vOut->z = (vec1->x * vec2->y) - (vec1->y * vec2->x);
    return NML_SUCCESS;
}

int Vec3Add(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut) {
    vOut->x = vec1->x + vec2->x;
    vOut->y = vec1->y + vec2->y;
    vOut->z = vec1->z + vec2->z;
    return NML_SUCCESS;
}

int Vec3Sub(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut) {
    vOut->x = vec1->x - vec2->x;
    vOut->y = vec1->y - vec2->y;
    vOut->z = vec1->z - vec2->z;
    return NML_SUCCESS;
}

int Vec3Mul(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut) {
    vOut->x = vec1->x * vec2->x;
    vOut->y = vec1->y * vec2->y;
    vOut->z = vec1->z * vec2->z;
    return NML_SUCCESS;
}

int Vec3Div(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut) {
    if (fabs(vec2->x) < kEPSILON || fabs(vec2->y) < kEPSILON ||
        fabs(vec2->z) < kEPSILON) {
        return NML_EZERODIV;
    }

    vOut->x = vec1->x / vec2->x;
    vOut->y = vec1->y / vec2->y;
    vOut->z = vec1->z / vec2->z;
    return NML_SUCCESS;
}

int Vec3Scale(Vec3 *vec, nml_t s, Vec3 *vOut) {
    vOut->x = vec->x * s;
    vOut->y = vec->y * s;
    vOut->z = vec->z * s;
    return NML_SUCCESS;
}

int Vec3Negate(Vec3 *vec, Vec3 *vOut) {
    vOut->x = -vec->x;
    vOut->y = -vec->y;
    vOut->z = -vec->z;
    return NML_SUCCESS;
}

int Vec3Project(Vec3 *vec1, Vec3 *vec3, Vec3 *vOut) {
    nml_t lenSqr = Vec3LengthSqr(vec3);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t scaler = Vec3Dot(vec1, vec3) / lenSqr;
    vOut->x = vec3->x * scaler;
    vOut->y = vec3->y * scaler;
    vOut->z = vec3->z * scaler;
    return NML_SUCCESS;
}

int Vec3Reject(Vec3 *vec1, Vec3 *vec3, Vec3 *vOut) {
    nml_t lenSqr = Vec3LengthSqr(vec3);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t dot = Vec3Dot(vec1, vec3);
    nml_t scaler = dot / lenSqr;

    vOut->x = vec1->x - (scaler * vec3->x);
    vOut->y = vec1->y - (scaler * vec3->y);
    vOut->z = vec1->z - (scaler * vec3->z);
    return NML_SUCCESS;
}

int Vec3Reflect(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut) {
    nml_t lenSqr = Vec3LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t scaler = 2.0 * Vec3Dot(vec1, vec2) / lenSqr;
    vOut->x = vec1->x - scaler * vec2->x;
    vOut->y = vec1->y - scaler * vec2->y;
    vOut->z = vec1->z - scaler * vec2->z;
    return NML_SUCCESS;
}
