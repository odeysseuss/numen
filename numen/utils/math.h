#ifndef __MATH_H__
#define __MATH_H__

#include "consts.h"
#include <math.h>
#include <stdint.h>

// helper macro functions
#define IS_ODD(n) ((n) & 1)
#define IS_EVEN(n) ((n) & 0)
#define SIGN(n) ((x) >= 0.0 ? 1 : -1)
#define MIN(a, b) ((a) < (b) ? a : b)
#define MAX(a, b) ((a) > (b) ? a : b)

static inline nml_t Sqr(nml_t n) {
    return  n * n;
}

static inline int is_int(nml_t n) {
    return (n == floor(n)) ? 0 : -1;
}

static inline int is_uint(nml_t n) {
    return (n >= 0 && n == floor(n)) ? 0 : -1;
}

// clang-format off
static const uint64_t LUT_FACTORIAL[21] = {
    1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800,
    39916800, 479001600, 6227020800, 87178291200, 1307674368000,
    20922789888000, 355687428096000, 6402373705728000,
    121645100408832000, 2432902008176640000
};
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

nml_t DegreesToRads(nml_t n);
nml_t RadstoDegs(nml_t n);
nml_t PowInt(nml_t x, int32_t n);
nml_t PowUInt(nml_t x, uint32_t n);
nml_t Sqrt(nml_t n);  // same as RSqrt but adjusted for sqrt
nml_t RSqrt(nml_t n); // Quake III fast inverse square root algorithm
nml_t Factorial(nml_t n); // lookup table for n <= 20
                          // stirlings approximation for n > 20
                          // and for non integer factorials uses gamma function

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !__MATH_H__
