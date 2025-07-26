#ifndef __VEC2D_H__
#define __VEC2D_H__

#include "utils/consts.h"
#include <stdbool.h>

typedef union Vec2 {
    struct {
        nml_t x;
        nml_t y;
    };
    nml_t Elements[2];
} Vec2;

// initialize a vector with all the elements set to 0.0f
Vec2 Vec2InitZero(void);
Vec2 Vec2Init(nml_t x, nml_t y);

nml_t Vec2Length(Vec2 vec);
nml_t Vec2LengthSqr(Vec2 vec);
Vec2 Vec2Normalize(Vec2 vec);

Vec2 Vec2Add(Vec2 vec1, Vec2 vec2);
// subtract vec2 form vec1
Vec2 Vec2Sub(Vec2 vec1, Vec2 vec2);
Vec2 Vec2Mul(Vec2 vec1, Vec2 vec2);
// divide vec1 by vec2
Vec2 Vec2Div(Vec2 vec1, Vec2 vec2);

nml_t Vec2Dot(Vec2 vec1, Vec2 vec2);
nml_t Vec2Cross(Vec2 vec1, Vec2 vec2);

Vec2 Vec2Scale(Vec2 vec, nml_t s);
Vec2 Vec2Negate(Vec2 vec);

// projection of vec1 on vec2
Vec2 Vec2Project(Vec2 vec1, Vec2 vec2);
// rejection of vec1 from vec2
Vec2 Vec2Reject(Vec2 vec1, Vec2 vec2);
// reflection of vec1 from vec2
Vec2 Vec2Reflect(Vec2 vec1, Vec2 vec2);

/*
 * vector utilities
 */

bool Vec2IsZero(Vec2 vec);

#endif // !__VEC2D_H__
