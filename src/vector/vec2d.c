#include "vector/vec2d.h"
#include "utils/math.h"
#include "utils/errors.h"

int Vec2Init(nml_t x, nml_t y, Vec2 *vOut) {
    vOut->x = x;
    vOut->y = y;
    return NML_SUCCESS;
}

int Vec2InitZero(Vec2 *vOut) {
    return Vec2Init(0, 0, vOut);
}

nml_t Vec2Length(Vec2 *vec) {
    return sqrt(Sqr(vec->x) + Sqr(vec->y));
}

nml_t Vec2LengthSqr(Vec2 *vec) {
    return Sqr(vec->x) + Sqr(vec->y);
}

int Vec2Normalize(Vec2 *vec, Vec2 *vOut) {
    if (Vec2IsZero(vec))
        return NML_EZERODIV;
    nml_t l = 1.0 / Vec2Length(vec);
    vOut->x = vec->x * l;
    vOut->y = vec->y * l;
    return NML_SUCCESS;
}

nml_t Vec2Dot(Vec2 *vec1, Vec2 *vec2) {
    return (vec1->x * vec2->x + vec1->y * vec2->y);
}

nml_t Vec2Cross(Vec2 *vec1, Vec2 *vec2) {
    return (vec1->x * vec2->y - vec1->y * vec2->x);
}

int Vec2Add(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    vOut->x = vec1->x + vec2->x;
    vOut->y = vec1->y + vec2->y;
    return NML_SUCCESS;
}

int Vec2Sub(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    vOut->x = vec1->x - vec2->x;
    vOut->y = vec1->y - vec2->y;
    return NML_SUCCESS;
}

int Vec2Mul(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    if (fabs(vec2->x) < kEPSILON || fabs(vec2->y) < kEPSILON)
        return NML_EZERODIV;

    vOut->x = vec1->x * vec2->x;
    vOut->y = vec1->y * vec2->y;
    return NML_SUCCESS;
}

int Vec2Div(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    if (fabs(vec2->x) < kEPSILON || fabs(vec2->y) < kEPSILON)
        return NML_EZERODIV;

    vOut->x = vec1->x / vec2->x;
    vOut->y = vec1->y / vec2->y;
    return NML_SUCCESS;
}

int Vec2Scale(Vec2 *vec, nml_t s, Vec2 *vOut) {
    vOut->x = vec->x * s;
    vOut->y = vec->y * s;
    return NML_SUCCESS;
}

int Vec2Negate(Vec2 *vec, Vec2 *vOut) {
    vOut->x = -vec->x;
    vOut->y = -vec->y;
    return NML_SUCCESS;
}

int Vec2Project(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    nml_t lenSqr = Vec2LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t scaler = Vec2Dot(vec1, vec2) / lenSqr;
    vOut->x = vec2->x * scaler;
    vOut->y = vec2->y * scaler;
    return NML_SUCCESS;
}

int Vec2Reject(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    nml_t lenSqr = Vec2LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t dot = Vec2Dot(vec1, vec2);
    nml_t scaler = dot / lenSqr;

    vOut->x = vec1->x - (scaler * vec2->x);
    vOut->y = vec1->y - (scaler * vec2->y);
    return NML_SUCCESS;
}

int Vec2Reflect(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    nml_t lenSqr = Vec2LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t scaler = 2.0 * Vec2Dot(vec1, vec2) / lenSqr;
    vOut->x = vec1->x - scaler * vec2->x;
    vOut->y = vec1->y - scaler * vec2->y;
    return NML_SUCCESS;
}
