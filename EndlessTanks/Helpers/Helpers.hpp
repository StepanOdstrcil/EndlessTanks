#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h> // For HRESULT

// From DXSampleHelper.h 
// Source: https://github.com/Microsoft/DirectX-Graphics-Samples
inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        throw std::exception();
    }
}

//inline float RadToDeg(float angleRad)
//{
//    return angleRad * RAD_TO_DEG;
//}
//
//inline float DegToRad(float angleDeg)
//{
//    return angleDeg * DEG_TO_RAD;
//}
