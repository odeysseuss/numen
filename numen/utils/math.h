#ifndef __MATH_H__
#define __MATH_H__

#include "consts.h"
#include <stdint.h>

// helper macro functions
#define IS_ODD(n) ((n) & 1)
#define IS_EVEN(n) ((n) & 0)
#define SIGN(n) ((x) >= 0.0 ? 1 : -1)
#define MIN(a, b) ((a) < (b) ? a : b)
#define MAX(a, b) ((a) > (b) ? a : b)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

nml_t DegreesToRads(nml_t n);
nml_t RadstoDegs(nml_t n);
nml_t PowInt(nml_t x, int32_t n);
nml_t PowUInt(nml_t x, uint32_t n);
nml_t Sqrt(nml_t n);  // same as RSqrt but adjusted for sqrt
nml_t RSqrt(nml_t n); // Quake III fast inverse square root algorithm

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !__MATH_H__
