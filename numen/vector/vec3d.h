#ifndef __VEC3D_H__
#define __VEC3D_H__

#include "utils/consts.h"
#include <stdbool.h>

typedef union vec3 {
    struct {
        nml_t x;
        nml_t y;
        nml_t z;
    };
    nml_t Elements[3];
} Vec3;

// initialize a vector with all the elements set to zero
int Vec3InitZero(Vec3 *vOut);
int Vec3Init(nml_t x, nml_t y, nml_t z, Vec3 *vOut);

nml_t Vec3Length(Vec3 *vec);
nml_t Vec3LengthSqr(Vec3 *vec);
int Vec3Normalize(Vec3 *vec, Vec3 *vOut);

int Vec3Add(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut);
// subtract vec2 form vec1
int Vec3Sub(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut);
int Vec3Mul(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut);
// divide vec1 by vec2
int Vec3Div(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut);

nml_t Vec3Dot(Vec3 *vec1, Vec3 *vec2);
int Vec3Cross(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut);

int Vec3Scale(Vec3 *vec, nml_t s, Vec3 *vOut);
int Vec3Negate(Vec3 *vec, Vec3 *vOut);

// projection of vec1 on vec2
int Vec3Project(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut);
// rejection of vec1 from vec2
int Vec3Reject(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut);
// reflection of vec1 from vec2
int Vec3Reflect(Vec3 *vec1, Vec3 *vec2, Vec3 *vOut);

/*
 * vector utilities
 */

static inline bool Vec3IsZero(Vec3 *vec) {
    return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z) <
           (kEPSILON * kEPSILON);
}

#endif // !__VEC3D_H__
