//
//  Rasterizer.cpp
//  softrender
//
//  Created by Jormungand on 2025/11/20.
//

#include "Rasterizer.hpp"
#include <cmath>
#include <algorithm>

namespace SoftRenderer {

    // 辅助函数：计算三角形 (v0, v1, v2) 的面积的两倍 (用于优化)
    // 在 2D 中，可以使用叉积的 z 分量来计算有向面积的两倍
    // 公式: (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0)
    inline float edgeFunction(const Vertex &v0, const Vertex &v1, const Vertex &v2) {
        return (v1.x - v0.x) * (v2.y - v0.y) - (v1.y - v0.y) * (v2.x - v0.x);
    }

    /**
     * 计算给定点 P(x, y) 的重心坐标
     * @param Px, Py 待测试点的坐标
     * @param v0, v1, v2 三角形的顶点
     * @param w0, w1, w2 用于返回的三个重心坐标（作为输出参数）
     * @return 三角形的面积的两倍 (用于后续归一化)，如果面积为 0 则返回 0
     */

    void Rasterizer::drawTriangle(FrameBuffer &fb, const Vertex &v0, const Vertex &v1, const Vertex &v2, const YUVTexture &texture) {
        // 1. 计算三角形的包围盒
        // 确定 x 轴的最小和最大边界，并钳制在 FrameBuffer 范围内 [0, width-1]
        int minX = static_cast<int>(std::floor(std::min({v0.x, v1.x, v2.x})));
        int maxX = static_cast<int>(std::ceil(std::max({v0.x, v1.x, v2.x})));

        // 确定 y 轴的最小和最大边界，并钳制在 FrameBuffer 范围内 [0, height-1]
        int minY = static_cast<int>(std::floor(std::min({v0.y, v1.y, v2.y})));
        int maxY = static_cast<int>(std::ceil(std::max({v0.y, v1.y, v2.y})));

        // 确保包围盒不会超出 FrameBuffer 的边界
        minX = std::max(0, minX);
        maxX = std::min(fb.getWidth() - 1, maxX);
        minY = std::max(0, minY);
        maxY = std::min(fb.getHeight() - 1, maxY);

        // 2. 遍历三角形包围盒
        for (int x = minX; x <= maxX; ++x)
        {
            for (int y = minY; y <= maxY; ++y)
            {
                // 3. 点在三角形内的测试（重心坐标法或边函数法）

                // 计算重心坐标或边函数，判断点 (x, y) 是否在三角形内
                // 如果在三角形内，进行插值计算纹理坐标
                if (在三角形内)
                {
                    // 插值纹理坐标
                    float u = 插值(u0, u1, u2);
                    float v = 插值(v0, v1, v2);

                    // 采样YUV
                    unsigned char y, u_val, v_val;
                    texture.sampleYUV(u, v, y, u_val, v_val);

                    // 颜色空间转换
                    Color rgb = ColorSpace::yuvToRGB(y, u_val, v_val);

                    // 输出到帧缓冲
                    fb.setPixel(x, y, rgb);
                }
            }
        }
    }

} // namespace SoftRenderer