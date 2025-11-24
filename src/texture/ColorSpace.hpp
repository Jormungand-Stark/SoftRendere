//
//  ColorSpace.hpp
//  softrender
//
//  Created by Jormungand on 2025/11/20.
//

#ifndef ColorSpace_hpp
#define ColorSpace_hpp

#include <stdio.h>
#include "core/Color.hpp"

namespace SoftRenderer {
    enum class ColorSpaceStandard {
        BT601, // 标清电视标准
        BT709, // 高清
        BT2020 // 超高清
    };

    namespace ColorCoefficients {
        namespace BT601 {
            constexpr float CrtoR = 1.402f;
            constexpr float CbtoG = -0.344136f;
            constexpr float CrtoG = -0.714136f;
            constexpr float CbtoB = 1.772f;
        }

        namespace BT709 {
            constexpr float CrtoR = 1.5748f;
            constexpr float CbtoG = -0.4681f; // 修正符号：影响 G = Y + CbtoG * U + CrtoG * V
            constexpr float CrtoG = -1.0459f; // 若为 + 值，则方向错误
            constexpr float CbtoB = 1.8556f;
        }

        namespace BT2020 {
            constexpr float CrtoR = 1.4746f;
            constexpr float CbtoG = -0.1646f;
            constexpr float CrtoG = -0.5713f;
            constexpr float CbtoB = 1.8814f;
        }
    }

    /**
     * 将YUV颜色空间转换为RGB颜色空间
     * @param y 亮度分量
     * @param u 色度分量U
     * @param v 色度分量V
     * @param standard 颜色空间标准
     * @return 转换后的RGB颜色
     */
    Color yuvToRGB(unsigned char y, unsigned char u, unsigned char v, ColorSpaceStandard standard = ColorSpaceStandard::BT601);

} // namespace SoftRenderer

#endif /* ColorSpace_hpp */
