#pragma once

// SIMD detection utility

#if defined(_MSC_VER)
    #include <intrin.h>
#else
    #include <cpuid.h>
#endif

#include <cstdint>

enum SIMDLevel {
    SIMD_NONE = 0,
    SIMD_SSE41 = 1,
    SIMD_AVX = 2,
    SIMD_AVX2 = 3,
    SIMD_AVX512 = 4
};

inline void cpuid_info(int out[4], int function_id, int subfunction_id = 0) {
#if defined(_MSC_VER)
    __cpuidex(out, function_id, subfunction_id);
#else
    __cpuid_count(function_id, subfunction_id, out[0], out[1], out[2], out[3]);
#endif
}

inline SIMDLevel detectSIMDLevel() {
    static SIMDLevel cachedLevel = []() -> SIMDLevel {
        int info[4] = {};
        cpuid_info(info, 0);
        int maxFuncId = info[0];

        bool sse41 = false;
        bool avx = false;
        bool avx2 = false;
        bool avx512f = false;
        bool os_avx_support = false;
        bool os_avx512_support = false;

        if (maxFuncId >= 1) {
            cpuid_info(info, 1);
            sse41 = (info[2] & (1 << 19)) != 0;
            avx   = (info[2] & (1 << 28)) != 0;

            if ((info[2] & (1 << 27)) != 0) {
#if defined(_MSC_VER)
                unsigned long long xcrFeatureMask = _xgetbv(0);
#else
                uint32_t eax, edx;
                __asm__ volatile (
                    "xgetbv"
                    : "=a"(eax), "=d"(edx)
                    : "c"(0)
                );
                uint64_t xcrFeatureMask = ((uint64_t)edx << 32) | eax;
#endif
                os_avx_support = (xcrFeatureMask & 0x6) == 0x6;
                os_avx512_support = (xcrFeatureMask & 0xE6) == 0xE6;
            }
        }

        if (maxFuncId >= 7) {
            cpuid_info(info, 7);
            avx2    = (info[1] & (1 << 5)) != 0;
            avx512f = (info[1] & (1 << 16)) != 0;
        }

        if (avx512f && os_avx512_support) return SIMD_AVX512;
        if (avx2 && os_avx_support)       return SIMD_AVX2;
        if (avx && os_avx_support)        return SIMD_AVX;
        if (sse41)                        return SIMD_SSE41;
        return SIMD_NONE;
    }();

    return cachedLevel;
}
