#ifndef __VEC4D_H__
#define __VEC4D_H__

#include "utils/consts.h"
#include <stdbool.h>

typedef union Vec4 {
    struct {
        nml_t x, y, z, w;
    };
    nml_t elems[4];
} Vec4;

// initialize a vector with all the elements set to 0.0f
int vec4InitZero(Vec4 *vOut);
int vec4Init(nml_t x, nml_t y, nml_t z, nml_t w, Vec4 *vOut);

nml_t vec4Length(Vec4 *vec);
nml_t vec4LengthSqr(Vec4 *vec);
int vec4Normalize(Vec4 *vec, Vec4 *vOut);

int vec4Add(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);
// subtract vec2 form vec1
int vec4Sub(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);
int vec4Mul(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);
// divide vec1 by vec2
int vec4Div(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);

nml_t vec4Dot(Vec4 *vec1, Vec4 *vec2);
int vec4Cross(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);

int vec4Scale(Vec4 *vec, nml_t s, Vec4 *vOut);
int vec4Negate(Vec4 *vec, Vec4 *vOut);

// projection of vec1 on vec2
int vec4Project(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);
// rejection of vec1 from vec2
int vec4Reject(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);
// reflection of vec1 from vec2
int vec4Reflect(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);

/*
 * vector utilities
 */

static inline bool vec4IsZero(Vec4 *vec) {
    return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z + vec->w * vec->w) <
           (kEPSILON * kEPSILON);
}

#endif // !__VEC4D_H__
