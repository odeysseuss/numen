#ifndef __SIMD_H__
#define __SIMD_H__

#if defined(_MSC_VER)
#define ALIGN_16 __declspec(align(16))
#else
#define ALIGN_16 __attribute__((aligned(16)))
#endif

// SIMD support
#if !defined(DISABLE_SIMD)

// x86/x64: SSE2
#if defined(__SSE2__) || defined(__x86_64__) || defined(_M_X64) || \
    defined(_M_AMD64) || defined(__i386__) || defined(_M_IX86)
#include <emmintrin.h>
#define USE_SIMD__SSE

// ARM: NEON (AArch64 or ARMv7+NEON)
#elif defined(__aarch64__) || defined(__ARM_NEON) || defined(__ARM_NEON__) || \
    defined(_M_ARM64) ||                                                      \
    (defined(_M_ARM) && (defined(__ARM_NEON) || defined(__ARM_NEON__)))
#include <arm_neon.h>
#define USE_SIMD__NEON

// No SIMD support
#else
#define DISABLE_SIMD
#endif

#endif

#endif // !__SIMD_H__
