#include "vector/vec2d.h"
#include "utils/math.h"

bool Vec2IsZero(Vec2 vec) {
    return (vec.x * vec.x + vec.y * vec.y) < (kEPSILON * kEPSILON);
}

Vec2 Vec2Init(nml_t x, nml_t y) {
    Vec2 vOut;
    vOut.x = x;
    vOut.y = y;
    return vOut;
}

Vec2 Vec2InitZero(void) {
    return Vec2Init(0.0, 0.0);
}

nml_t Vec2Length(Vec2 vec) {
    return Sqrt(Sqr(vec.x) + Sqr(vec.y));
}

nml_t Vec2LengthSqr(Vec2 vec) {
    return Sqr(vec.x) + Sqr(vec.y);
}

Vec2 Vec2Normalize(Vec2 vec) {
    if (Vec2IsZero(vec)) return vec;
    Vec2 vOut;
    nml_t l = 1.0 / Vec2Length(vec);
    vOut.x = vec.x * l;
    vOut.y = vec.y * l;
    return vOut;
}

nml_t Vec2Dot(Vec2 vec1, Vec2 vec2) {
    return (vec1.x * vec2.x + vec1.y * vec2.y);
}

nml_t Vec2Cross(Vec2 vec1, Vec2 vec2) {
    return (vec1.x * vec2.y - vec1.y * vec2.x);
}

Vec2 Vec2Add(Vec2 vec1, Vec2 vec2) {
    Vec2 vOut;
    vOut.x = vec1.x + vec2.x;
    vOut.y = vec1.y + vec2.y;
    return vOut;
}

Vec2 Vec2Sub(Vec2 vec1, Vec2 vec2) {
    Vec2 vOut;
    vOut.x = vec1.x - vec2.x;
    vOut.y = vec1.y - vec2.y;
    return vOut;
}

Vec2 Vec2Mul(Vec2 vec1, Vec2 vec2) {
    Vec2 vOut;
    vOut.x = vec1.x * vec2.x;
    vOut.y = vec1.y * vec2.y;
    return vOut;
}

Vec2 Vec2Div(Vec2 vec1, Vec2 vec2) {
    Vec2 vOut;
    vOut.x = vec1.x / vec2.x;
    vOut.y = vec1.y / vec2.y;
    return vOut;
}

Vec2 Vec2Scale(Vec2 vec, nml_t s) {
    Vec2 vOut;
    vOut.x = vec.x * s;
    vOut.y = vec.y * s;
    return vOut;
}

Vec2 Vec2Negate(Vec2 vec) {
    Vec2 vOut;
    vOut.x = -vec.x;
    vOut.y = -vec.y;
    return vOut;
}

Vec2 Vec2Project(Vec2 vec1, Vec2 vec2) {
    nml_t dotVec = Vec2Dot(vec1, vec2);
    nml_t scaler = dotVec / Vec2LengthSqr(vec2);
    Vec2 vOut = Vec2Scale(vec2, scaler);
    return vOut;
}

Vec2 Vec2Reject(Vec2 vec1, Vec2 vec2) {
    Vec2 project = Vec2Project(vec1, vec2);
    Vec2 vOut = Vec2Sub(vec1, project);
    return vOut;
}

Vec2 Vec2Reflect(Vec2 vec1, Vec2 vec2) {
    Vec2 project = Vec2Project(vec1, vec2);
    Vec2 projectMul2 = Vec2Scale(project, 2);
    Vec2 vOut = Vec2Sub(projectMul2, vec1);
    return vOut;
}
