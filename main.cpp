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

    std::cout << "{ 0.852, -0.001, -0.496, 0.165 }" << std::endl;

    const __m128 qSSE = _mm_setr_ps(0.852f, -0.001f, -0.496f,  0.165f);

    u32 cqSSE = QuaternionCompressor::Compress(qSSE);

    std::cout << cqSSE << std::endl;

    getchar();

    return 0;
}

