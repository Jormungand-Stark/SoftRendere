//
//  FrameBuffer.cpp
//  softrender
//
//  Created by Jormungand on 2025/11/20.
//

#include "FrameBuffer.hpp"

void FrameBuffer::clear(const Color& clear_color) {
    std::fill(pixels.begin(), pixels.end(), clear_color);
}

bool FrameBuffer::saveToPPM(std::string filename) {
    std::ofstream ofs(filename, std::ios::binary);
    
    return true;
}

void FrameBuffer::setPixel(int x, int y, const Color& color) {
    // 由于 unsigned char 天然就是 0 到 255（或 0 到 256 个值），因此无需对 color 做判断。
    if (x >= 0 && x <= width && y >= 0 && y <= height) {
        int index = y * width + x;
        pixels[index] = color;
    }
}

Color FrameBuffer::getPixel(int x, int y) const {
    int index = y * width + x;
    return pixels[index];
}
