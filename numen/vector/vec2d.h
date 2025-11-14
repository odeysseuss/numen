#ifndef __VEC2D_H__
#define __VEC2D_H__

#include "utils/consts.h"
#include <stdbool.h>

typedef union Vec2 {
    struct {
        nml_t x, y;
    };
    nml_t elems[2];
} Vec2;

// initialize a vector with all the elements set to 0.0f
int vec2InitZero(Vec2 *vOut);
int vec2Init(nml_t x, nml_t y, Vec2 *vOut);

nml_t vec2Length(Vec2 *vec);
nml_t vec2LengthSqr(Vec2 *vec);
int vec2Normalize(Vec2 *vec, Vec2 *vOut);

int vec2Add(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);
// subtract vec2 form vec1
int vec2Sub(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);
int vec2Mul(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);
// divide vec1 by vec2
int vec2Div(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);

nml_t vec2Dot(Vec2 *vec1, Vec2 *vec2);
nml_t vec2Cross(Vec2 *vec1, Vec2 *vec2);

int vec2Scale(Vec2 *vec, nml_t s, Vec2 *vOut);
int vec2Negate(Vec2 *vec, Vec2 *vOut);

// projection of vec1 on vec2
int vec2Project(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);
// rejection of vec1 from vec2
int vec2Reject(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);
// reflection of vec1 from vec2
int vec2Reflect(Vec2 *vec1, Vec2 *vec2, Vec2 *vOut);

/*
 * vector utilities
 */

static inline bool vec2IsZero(Vec2 *vec) {
    return (vec->x * vec->x + vec->y * vec->y) < (kEPSILON * kEPSILON);
}

#endif // !__VEC2D_H__
