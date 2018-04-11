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
    Quat q = { 0.852f, -0.001f, -0.496f,  0.165f };

    q << std::cout;

    u32 cq = QuaternionCompressor::Compress(q.x, q.y, q.z, q.w);

    std::cout << cq << std::endl;

    QuaternionCompressor::Uncompress(cq, q.x, q.y, q.z, q.w);

    q << std::cout;

    getchar();

    return 0;
}

