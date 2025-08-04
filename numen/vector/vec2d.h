#ifndef __VEC2D_H__
#define __VEC2D_H__

#include "utils/consts.h"
#include <stdbool.h>

typedef union Vec2 {
    struct {
        nml_t x, y;
    };
    nml_t Elements[2];
} Vec2;

// initialize a vector with all the elements set to 0.0f
int Vec2InitZero(Vec2 *vOut);
int Vec2Init(nml_t x, nml_t y, Vec2 *vOut);

nml_t Vec2Length(Vec2 *vec);
nml_t Vec2LengthSqr(Vec2 *vec);
int Vec2Normalize(Vec2 *vec, Vec2 *vOut);

int Vec2Add(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);
// subtract vec2 form vec1
int Vec2Sub(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);
int Vec2Mul(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);
// divide vec1 by vec2
int Vec2Div(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);

nml_t Vec2Dot(Vec2 *vec1, Vec2 *vec2);
nml_t Vec2Cross(Vec2 *vec1, Vec2 *vec2);

int Vec2Scale(Vec2 *vec, nml_t s, Vec2 *vOut);
int Vec2Negate(Vec2 *vec, Vec2 *vOut);

// projection of vec1 on vec2
int Vec2Project(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);
// rejection of vec1 from vec2
int Vec2Reject(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);
// reflection of vec1 from vec2
int Vec2Reflect(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);

/*
 * vector utilities
 */

static inline bool Vec2IsZero(Vec2 *vec) {
    return (vec->x * vec->x + vec->y * vec->y) < (kEPSILON * kEPSILON);
}

#endif // !__VEC2D_H__
