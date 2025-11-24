//
//  ColorSpace.cpp
//  softrender
//
//  Created by Jormungand on 2025/11/20.
//

#include <algorithm>
#include "ColorSpace.hpp"

inline unsigned char clampColorComponent(float value) {
    return static_cast<unsigned char>(
        std::min(std::max(value, 0.0f), 255.0f)
    );
}

Color SoftRenderer::yuvToRGB(unsigned char y, unsigned char u, unsigned char v, ColorSpaceStandard standard) {
    /**
     * 基于 8 位整数 (0-255) 的 YUV (YCbCr) 到 RGB 的转换公式如下：
     * R = Y + 1.402 × (V - 128)
     * G = Y - 0.344136 × (U - 128) - 0.714136 × (V - 128)
     * B = Y + 1.772 × (U - 128)
     */
    // YUV 的浮点值，将 U/V 偏移到中心范围 [-128, 127]
    const float Y = static_cast<float>(y);
    const float U = static_cast<float>(u) - 128.0f;
    const float V = static_cast<float>(v) - 128.0f;

    // 系数变量（由 switch 决定）
    float CrtoR, CbtoG, CrtoG, CbtoB;
    
    switch (standard) {
        case ColorSpaceStandard::BT601:
            // ITU-R BT.601 (SDTV, 常用标准)，不同标准有不同的系数，根据基色推导而来。
            CrtoR = ColorCoefficients::BT601::CrtoR;
            CbtoG = ColorCoefficients::BT601::CbtoG;
            CrtoG = ColorCoefficients::BT601::CrtoG;
            CbtoB = ColorCoefficients::BT601::CbtoB;
            
            break;
        case ColorSpaceStandard::BT709:
            // ITU-R BT.709 (HDTV)
            // BT.709 的系数不同，通常用于高清视频
            CrtoR = ColorCoefficients::BT709::CrtoR;
            CbtoG = ColorCoefficients::BT709::CbtoG;
            CrtoG = ColorCoefficients::BT709::CrtoG;
            CbtoB = ColorCoefficients::BT709::CbtoB;
            
            break;
        case ColorSpaceStandard::BT2020:
            // ITU-R BT.2020 (UHDTV)
            // BT.2020 的系数更复杂，且通常与 10-bit 或 12-bit 数据相关。
            // 这里的公式仅为占位，需要根据实际需求确定系数。
            // 暂时使用 BT.709 系数作为占位，避免编译错误
            CrtoR = ColorCoefficients::BT2020::CrtoR;
            CbtoG = ColorCoefficients::BT2020::CbtoG;
            CrtoG = ColorCoefficients::BT2020::CrtoG;
            CbtoB = ColorCoefficients::BT2020::CbtoB;
            
            break;
    }
    
    const float R = Y + CrtoR * V;
    const float G = Y + CbtoG * U + CrtoG * V;
    const float B = Y + CbtoB * U;

    // 将最终计算的 RGB 浮点值限制在 [0, 255] 范围内
    return Color(
        clampColorComponent(R),
        clampColorComponent(G),
        clampColorComponent(B)
    );
}
