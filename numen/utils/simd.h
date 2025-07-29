#ifndef __SIMD_H__
#define __SIMD_H__

// SIMD support
#if !defined(DISABLE_SIMD)
#if defined(__SSE2__) || defined(__x86_64__) || defined(_M_X64) || \
    defined(_M_AMD64) || defined(__i386__) || defined(_M_IX86)
#include <emmintrin.h>
#define USE_SIMD__SSE

#elif defined(__aarch64__) || defined(__ARM_NEON) || defined(__ARM_NEON__) || \
    defined(_M_ARM64) || (defined(_M_ARM) && defined(_M_ARMT))
#include <arm_neon.h>
#define USE_SIMD__NEON

#else
#define DISABLE_SIMD
#endif
#endif

#endif // !__SIMD_H__
