#include "vector/vec2d.h"
#include "utils/math.h"
#include "utils/errors.h"

int Vec2Init(nml_t x, nml_t y, Vec2 *vOut) {
    vOut->X = x;
    vOut->Y = y;
    return NML_SUCCESS;
}

int Vec2InitZero(Vec2 *vOut) {
    return Vec2Init(0, 0, vOut);
}

nml_t Vec2Length(Vec2 *vec) {
    return sqrt(Sqr(vec->X) + Sqr(vec->Y));
}

nml_t Vec2LengthSqr(Vec2 *vec) {
    return Sqr(vec->X) + Sqr(vec->Y);
}

int Vec2Normalize(Vec2 *vec, Vec2 *vOut) {
    if (Vec2IsZero(vec))
        return NML_EZERODIV;
    nml_t l = 1.0 / Vec2Length(vec);
    vOut->X = vec->X * l;
    vOut->Y = vec->Y * l;
    return NML_SUCCESS;
}

nml_t Vec2Dot(Vec2 *vec1, Vec2 *vec2) {
    return (vec1->X * vec2->X + vec1->Y * vec2->Y);
}

nml_t Vec2Cross(Vec2 *vec1, Vec2 *vec2) {
    return (vec1->X * vec2->Y - vec1->Y * vec2->X);
}

int Vec2Add(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    vOut->X = vec1->X + vec2->X;
    vOut->Y = vec1->Y + vec2->Y;
    return NML_SUCCESS;
}

int Vec2Sub(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    vOut->X = vec1->X - vec2->X;
    vOut->Y = vec1->Y - vec2->Y;
    return NML_SUCCESS;
}

int Vec2Mul(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    if (fabs(vec2->X) < kEPSILON || fabs(vec2->Y) < kEPSILON)
        return NML_EZERODIV;

    vOut->X = vec1->X * vec2->X;
    vOut->Y = vec1->Y * vec2->Y;
    return NML_SUCCESS;
}

int Vec2Div(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    if (fabs(vec2->X) < kEPSILON || fabs(vec2->Y) < kEPSILON)
        return NML_EZERODIV;

    vOut->X = vec1->X / vec2->X;
    vOut->Y = vec1->Y / vec2->Y;
    return NML_SUCCESS;
}

int Vec2Scale(Vec2 *vec, nml_t s, Vec2 *vOut) {
    vOut->X = vec->X * s;
    vOut->Y = vec->Y * s;
    return NML_SUCCESS;
}

int Vec2Negate(Vec2 *vec, Vec2 *vOut) {
    vOut->X = -vec->X;
    vOut->Y = -vec->Y;
    return NML_SUCCESS;
}

int Vec2Project(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    nml_t lenSqr = Vec2LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t scaler = Vec2Dot(vec1, vec2) / lenSqr;
    vOut->X = vec2->X * scaler;
    vOut->Y = vec2->Y * scaler;
    return NML_SUCCESS;
}

int Vec2Reject(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    nml_t lenSqr = Vec2LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t dot = Vec2Dot(vec1, vec2);
    nml_t scaler = dot / lenSqr;

    vOut->X = vec1->X - (scaler * vec2->X);
    vOut->Y = vec1->Y - (scaler * vec2->Y);
    return NML_SUCCESS;
}

int Vec2Reflect(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut) {
    nml_t lenSqr = Vec2LengthSqr(vec2);
    if (lenSqr < kEPSILON)
        return NML_EZERODIV;

    nml_t scaler = 2.0 * Vec2Dot(vec1, vec2) / lenSqr;
    vOut->X = vec1->X - scaler * vec2->X;
    vOut->Y = vec1->Y - scaler * vec2->Y;
    return NML_SUCCESS;
}
