// QuaternionCompressor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "QuaternionCompressor.h"


struct Quat
{
    float x, y, z, w;

    std::ostream& operator<<(std::ostream& os)
    {
        os << "{ " << x << ", " << y << ", " << z << ", " << w << " }" << std::endl;
        return os;
    }
};

int main()
{
    std::cout << "SCALAR VERSION" << std::endl;

    Quat q = { 0.852f, -0.001f, -0.496f,  0.165f };

    q << std::cout;

    u32 cq = QuaternionCompressor::Compress(q.x, q.y, q.z, q.w);

    std::cout << cq << std::endl;

    QuaternionCompressor::Uncompress(cq, q.x, q.y, q.z, q.w);

    q << std::cout;

    std::cout << std::endl;

    std::cout << "SSE VERSION" << std::endl;

    __m128 qSSE = _mm_setr_ps(0.852f, -0.001f, -0.496f,  0.165f);

    float *val = (float*)&qSSE;
    std::cout << "{ " << val[0] << ", " << val[1] << ", " << val[2] << ", " << val[3] << " }" << std::endl;

    u32 cqSSE = QuaternionCompressor::Compress(qSSE);

    std::cout << cqSSE << std::endl;

    QuaternionCompressor::Uncompress(cqSSE, qSSE);

    val = (float*)&qSSE;
    std::cout << "{ " << val[0] << ", " << val[1] << ", " << val[2] << ", " << val[3] << " }" << std::endl;

    getchar();

    return 0;
}

