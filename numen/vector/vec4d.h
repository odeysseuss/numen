#ifndef __VEC4D_H__
#define __VEC4D_H__

#include "utils/consts.h"
#include <stdbool.h>

typedef union NM_Vec4 {
    struct {
        nml_t x;
        nml_t y;
        nml_t z;
        nml_t w;
    };
    nml_t Elements[4];
} Vec4;

// initialize a vector with all the elements set to 0.0f
int Vec4InitZero(Vec4 *vOut);
int Vec4Init(nml_t x, nml_t y, nml_t z, nml_t w, Vec4 *vOut);

nml_t Vec4Length(Vec4 *vec);
nml_t Vec4LengthSqr(Vec4 *vec);
int Vec4Normalize(Vec4 *vec, Vec4 *vOut);

int Vec4Add(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);
// subtract vec2 form vec1
int Vec4Sub(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);
int Vec4Mul(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);
// divide vec1 by vec2
int Vec4Div(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);

nml_t Vec4Dot(Vec4 *vec1, Vec4 *vec2);
int Vec4Cross(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);

int Vec4Scale(Vec4 *vec, nml_t s, Vec4 *vOut);
int Vec4Negate(Vec4 *vec, Vec4 *vOut);

// projection of vec1 on vec2
int Vec4Project(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);
// rejection of vec1 from vec2
int Vec4Reject(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);
// reflection of vec1 from vec2
int Vec4Reflect(Vec4 *vec1, Vec4 *vec2, Vec4 *vOut);

/*
 * vector utilities
 */

static inline bool Vec4IsZero(Vec4 *vec) {
    return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z +
            vec->w * vec->w) < (kEPSILON * kEPSILON);
}

#endif // !__VEC4D_H__
