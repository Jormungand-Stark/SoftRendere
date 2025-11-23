//
//  Rasterizer.hpp
//  softrender
//
//  Created by Jormungand on 2025/11/20.
//

#ifndef Rasterizer_hpp
#define Rasterizer_hpp

#include <vector>
#include "geometry/Vertex.hpp"
#include "core/FrameBuffer.hpp"
#include "texture/YUVTexture.hpp"

// 光栅化
/**
 * YUVTexture (存储原始数据)
 *     ↓
 * Vertex几何 (定义三角形和纹理坐标)
 *     ↓
 * Rasterizer光栅化
 *     ├── 纹理采样 ← YUVTexture.sampleYUV()
 *     ├── 色彩空间转换 ← ColorSpace::yuvToRGB()
 *     └── 像素写入 ← FrameBuffer.setPixel()
 *     ↓
 * FrameBuffer (存储最终结果)
 */

namespace SoftRenderer {
    class Rasterizer {
    public:
        Rasterizer();
        ~Rasterizer();

        void rasterize();
        /**
         * 绘制三角形并进行纹理映射
         * @param fb 目标帧缓冲（包含尺寸），往哪里画
         * @param v0 三角形顶点0
         * @param v1 三角形顶点1
         * @param v2 三角形顶点2
         * @param texture 源纹理对象
         */
        void drawTriangle(FrameBuffer &fb, const Vertex &v0, const Vertex &v1, const Vertex &v2, const YUVTexture &texture);

    private:
        // 创建两个三角形表示矩形面片
        std::vector<Vertex> vertices = {
            // 三角形1：左下、右下、左上
            {0, 0, 0, 0},      // 左下，对应纹理左下坐标(0,0)
            {width, 0, 1, 0},  // 右下，纹理坐标(1,0)
            {0, height, 0, 1}, // 左上，纹理坐标(0,1)

            // 三角形2：右下、右上、左上
            {width, 0, 1, 0},      // 右下
            {width, height, 1, 1}, // 右上
            {0, height, 0, 1}      // 左上
        };

        int width;
        int height;
    };

} // namespace SoftRenderer

#endif /* Rasterizer_hpp */
