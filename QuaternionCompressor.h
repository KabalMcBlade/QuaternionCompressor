#pragma once

#include <cmath>

#define _127        127.0f
#define _1_Div_127  0.00787401574803149606299212598425f // 1.0f / 127.0f

typedef char s8;
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
};