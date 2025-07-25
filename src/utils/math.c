#include "utils/math.h"
#include "utils/consts.h"
#include "utils/errors.h"
#include <math.h>
#include <stdint.h>
#include <string.h>

nml_t PowInt(nml_t x, int32_t n) {
    // handle negative exponents by reciprocating the base
    if (n < 0) {
        x = 1.0 / x;
        n = -n; // safe for INT32_MIN due to unsigned conversion
    }
    return PowUInt(x, (uint32_t)n);
}

nml_t PowUInt(nml_t x, uint32_t n) {
    nml_t result = 1.0;

    // fast exponentiation (binary decomposition)
    while (n > 0) {
        if (n & 1) {     // LSB set?
            result *= x; // multiply if bit is active
        }
        x *= x;  // square the base
        n >>= 1; // shift to next bit
    }
    return result;
}

nml_t DegsToRads(nml_t n) {
    return n * kPI_180;
}

nml_t RadsToDegs(nml_t n) {
    return n * k180_PI;
}

nml_t Sqrt(nml_t n) {
    if (n < 0)
        return NML_EINVAL;
    // determine floating-point properties at compile time
    const uint8_t exponent_bits =
        (sizeof(nml_t) == 4) ? 8 : 11; // float:8, double:11
    const uint8_t mantissa_bits =
        (sizeof(nml_t) == 4) ? 23 : 52; // float:23, double:52
    const uint64_t exponent_bias =
        ((1ULL << (exponent_bits - 1)) - 1); // 127 or 1023

    // compute magic number
    const uint64_t magic = (exponent_bias * (1ULL << mantissa_bits)) * 3 / 2;

    // bit hack for initial guess (avoids strict-aliasing UB)
    uint64_t i;
    memcpy(&i, &n, sizeof(n)); // safe type-punning
    i = magic - (i >> 1);
    nml_t x;
    memcpy(&x, &i, sizeof(n)); // convert back to float/double

    // Newton-Raphson refinement (1-2 iterations)
    x = x * (1.5 - (0.5 * n * x * x));
    x = x * (1.5 - (0.5 * n * x * x));

    // Multiply by n to get sqrt(n) (since x ≈ 1/sqrt(n))
    return n * x;
}

nml_t RSqrt(nml_t n) {
    if (n < 0)
        return NML_EINVAL;
    // determine floating-point properties at compile time
    const uint8_t exponent_bits =
        (sizeof(nml_t) == 4) ? 8 : 11; // float:8, double:11
    const uint8_t mantissa_bits =
        (sizeof(nml_t) == 4) ? 23 : 52; // float:23, double:52
    const uint64_t exponent_bias =
        ((1ULL << (exponent_bits - 1)) - 1); // 127 or 1023

    // compute magic number
    const uint64_t magic = (exponent_bias * (1ULL << mantissa_bits)) * 3 / 2;

    // bit hack for initial guess
    uint64_t i;
    memcpy(&i, &n, sizeof(n)); // safe type punnin
    i = magic - (i >> 1);
    nml_t x;
    memcpy(&x, &i, sizeof(n)); // convert back to float/double

    // Newton-Raphson refinement (1-2 iterations)
    x = x * (1.5 - (0.5 * n * x * x));
    x = x * (1.5 - (0.5 * n * x * x));
    return x;
}

nml_t Factorial(nml_t n) {
    if (n < 0)
        return NML_EINVAL;
    if (is_uint(n) == 0) {
        if (n <= 20) {
            return LUT_FACTORIAL[(uint8_t)n];
        } else {
            const nml_t term1 = Sqrt(k2PI * n);
            const nml_t term2 = PowUInt((n / kE), n);
            const nml_t corr_factor = 1.0 + (1.0 / (12 * n)) +
                                      (1.0 / (288 * n * n)) -
                                      (139.0 / (51840 * n * n * n));
            return term1 * term2 * corr_factor;
        }
    } else {
        return tgamma(n + 1);
    }
}
