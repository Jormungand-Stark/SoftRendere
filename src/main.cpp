//
//  main.cpp
//  softrender
//
//  Created by 封睿文 on 2025/11/19.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// 定义颜色结构体，存储 RGB 三通道（每个通道 0-255）
struct Color {
    unsigned char r, g, b;
};

// 顶点结构体，包含二维坐标和颜色
struct Vertex {
    float x, y;   // 顶点坐标（屏幕空间）
    float u, v;   // 纹理坐标
    // NOTE: 在纹理渲染中可能不需要顶点颜色 color, 因为颜色来自纹理采样
    // Color color;  // 顶点颜色
};

int main() {
    std::cout << "Soft Renderer Started!" << std::endl;
    return 0;
}
