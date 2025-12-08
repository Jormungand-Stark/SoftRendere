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
        Rasterizer() = default;
        
        /**
         * 绘制三角形并进行纹理映射
         * @param fb 目标帧缓冲（包含尺寸），往哪里画
         * @param v0 三角形顶点0
         * @param v1 三角形顶点1
         * @param v2 三角形顶点2
         * @param texture 源纹理对象
         */
        void drawTexturedTriangle(FrameBuffer& fb,
                                  const Vertex& v0,
                                  const Vertex& v1,
                                  const Vertex& v2,
                                  const YUVTexture& texture);
        
        // 辅助方法：绘制纯色三角形（用于调试）
        void drawSolidTriangle(FrameBuffer& fb,
                               const Vertex& v0,
                               const Vertex& v1,
                               const Vertex& v2,
                               const Color& color);

    private:
    };

} // namespace SoftRenderer

#endif /* Rasterizer_hpp */
