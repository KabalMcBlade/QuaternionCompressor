#pragma once

#include <cmath>

//#define SIMD_ARCH_SSE41
//#define SIMD_ARCH_SSE3
#define SIMD_ARCH_SS2

#if defined(SIMD_ARCH_SSE41)
#   include <smmintrin.h>
#elif defined(SIMD_ARCH_SSE3)
#   include <pmmintrin.h>
#elif defined(SIMD_ARCH_SS2)
#   include <emmintrin.h>
#endif

#define MEMORY_ALIGNMENT(x)     __declspec(align(x))
#define MEMORY_ALIGNMENT_16     MEMORY_ALIGNMENT(16)


#define _127        127.0f
#define _1_Div_127  0.00787401574803149606299212598425f // 1.0f / 127.0f

typedef char s8;
typedef int s32;
typedef unsigned char u8;
typedef unsigned int u32;

/************************************************************************

The class assume the quaternion component floats are normalized, 
this because, you know, is a quaternion rotation!

 ************************************************************************/

class QuaternionCompressor final
{
public:
    static u32 Compress(float _x, float _y, float _z, float _w)
    {
        return (PackNormalizedFloat(_x) << 24 | PackNormalizedFloat(_y) << 16 | PackNormalizedFloat(_z) << 8 | PackNormalizedFloat(_w));
    }

    static void Uncompress(u32 _c, float& _x, float& _y, float& _z, float& _w)
    {
        _x = UnpackNormalizedFloat((_c >> 24) & 0xff);
        _y = UnpackNormalizedFloat((_c >> 16) & 0xff);
        _z = UnpackNormalizedFloat((_c >> 8) & 0xff);
        _w = UnpackNormalizedFloat(_c & 0xff);
    }

    static u32 Compress(const __m128& _q)
    {
        static MEMORY_ALIGNMENT_16 const __m128 multiplier127 { _127, _127, _127, _127 };

        const __m128 mul = _mm_mul_ps(_q, multiplier127);
        const __m128 rnd = _mm_round_ps(mul, 2);
        const __m128i ird = _mm_cvtps_epi32(rnd);

        u8 res[4];
        res[0] = _mm_cvtsi128_si32(_mm_shuffle_epi32(ird, _MM_SHUFFLE(0, 0, 0, 0)));
        res[1] = _mm_cvtsi128_si32(_mm_shuffle_epi32(ird, _MM_SHUFFLE(1, 1, 1, 1)));
        res[2] = _mm_cvtsi128_si32(_mm_shuffle_epi32(ird, _MM_SHUFFLE(2, 2, 2, 2)));
        res[3] = _mm_cvtsi128_si32(_mm_shuffle_epi32(ird, _MM_SHUFFLE(3, 3, 3, 3)));

        return (res[0] << 24 | res[1] << 16 | res[2] << 8 | res[3]);
    }

    static void Uncompress(u32 _c, __m128& _q)
    {
        const s8 w = (_c & 0xff);
        const s8 z = ((_c >> 8) & 0xff);
        const s8 y = ((_c >> 16) & 0xff);
        const s8 x = ((_c >> 24) & 0xff);

        static MEMORY_ALIGNMENT_16 const __m128 multiplier1Div127{ _1_Div_127, _1_Div_127, _1_Div_127, _1_Div_127 };
        const __m128i srci = _mm_set_epi32(w, z, y, x);
        const __m128  flt = _mm_cvtepi32_ps(srci);
        _q = _mm_mul_ps(flt, multiplier1Div127);
    }

private:
    static u8 PackNormalizedFloat(float _f)
    {
        const s8 pack(static_cast<s8>(round(_f * _127)));
        u8 data = 0;
        memcpy(&data, &pack, sizeof(data));
        return data;
    }

    static float UnpackNormalizedFloat(u8 _u)
    {
        s8 unpack = 0;
        memcpy(&unpack, &_u, sizeof(unpack));
        return static_cast<float>(unpack) * _1_Div_127;
    }



#if !defined(SIMD_ARCH_SSE41)
    static __m128 _mm_round_ps(const __m128& _a, int rounding = 2)
    {
        static const __m128 v0 = _mm_setzero_ps();

        const __m128 v1 = _mm_cmpeq_ps(v0, v0);
        const __m128 vNearest2 = *(__m128*)&_mm_srli_epi32(*(__m128i*)&v1, rounding);
        const __m128i i = _mm_cvttps_epi32(_a);
        const __m128 aTrunc = _mm_cvtepi32_ps(i); 
        const __m128 rmd = _mm_sub_ps(_a, aTrunc);
        const __m128 rmd2 = _mm_mul_ps(rmd, vNearest2); 
        const __m128i rmd2i = _mm_cvttps_epi32(rmd2); 
        const __m128 rmd2Trunc = _mm_cvtepi32_ps(rmd2i);
        const __m128 r = _mm_add_ps(aTrunc, rmd2Trunc);

        return r;
    }
#endif

};